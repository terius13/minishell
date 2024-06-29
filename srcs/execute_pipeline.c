/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:22:57 by ting              #+#    #+#             */
/*   Updated: 2024/06/29 14:01:46 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_dup(int num_cmds, int i, int **pipe_ends)
{
	if (i > 0)
		dup2(pipe_ends[i - 1][0], STDIN_FILENO);
	if (i < num_cmds - 1)
		dup2(pipe_ends[i][1], STDOUT_FILENO);
	close_pipe_ends(pipe_ends, num_cmds);
}

t_pipeline	*init_pipeline(t_cmd **cmds, t_env **env, t_ms_state *status)
{
	t_pipeline	*pipeline;

	pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!pipeline)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	pipeline->cmds = cmds;
	pipeline->env = env;
	pipeline->status = status;
	pipeline->num_cmds = cmds_len(*cmds);
	pipeline->pipe_ends = init_pipe_ends(pipeline->num_cmds);
	init_pipes(pipeline->pipe_ends, pipeline->num_cmds);
	return (pipeline);
}

void	parent_wait(t_ms_state *status, int num_cmds)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i++ < num_cmds)
	{
		wait(&exit_status);
		if (WIFEXITED(exit_status))
			status->exit_status = WEXITSTATUS(exit_status);
	}
}

void	execute_pipeline(t_cmd **cmds, t_env **env, t_ms_state *status)
{
	t_pipeline *pipeline;
	t_cmd *current;
	int i;
	int pid;

	pipeline = init_pipeline(cmds, env, status);
	current = *cmds;
	i = 0;
	while (current)
	{
		here_doc(current, env, status);
		pid = fork();
		if (pid < 0)
			return (perror("fork error"), free_pipe_ends(pipeline->pipe_ends,
					pipeline->num_cmds));
		if (pid == 0)
			execute_child_pipeline(pipeline, current, i);
		current = current->next;
		i++;
	}
	close_pipe_ends(pipeline->pipe_ends, pipeline->num_cmds);
	parent_wait(status, pipeline->num_cmds);
	free_pipe_ends(pipeline->pipe_ends, pipeline->num_cmds);
	free(pipeline);
}
