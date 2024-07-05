/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:22:57 by ting              #+#    #+#             */
/*   Updated: 2024/07/05 15:22:49 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	parent_wait(t_ms_state *status)
{
	int	exit_status;

	while (waitpid(-1, &exit_status, 0) > 0)
	{
		if (WIFEXITED(exit_status))
			status->exit_status = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
		{
			if (WTERMSIG(exit_status) == SIGINT)
			{
				status->exit_status = 130;
				g_reset_cancel = 3;
			}
			else if (WTERMSIG(exit_status) == SIGQUIT)
			{
				ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
				status->exit_status = 128 + WTERMSIG(exit_status);
			}
		}
	}
	if (g_reset_cancel == 3)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_reset_cancel = 0;
	}
}

void	execute_child_pipeline(t_pipeline *pipeline, t_cmd *current)
{
	init_dup(pipeline, current);
	do_redirection(current, pipeline->status);
	if (illegal_builtins(current))
		free_n_exit_child(pipeline);
	if (current->builtin)
		execute_builtins(&current, current->cmd_arr, pipeline->env,
			pipeline->status);
	else if (current->cmd_arr[0])
		execute_cmd(current, pipeline->env, pipeline->status);
	free_n_exit_child(pipeline);
}

void	run_command_pipeline(t_pipeline *pipeline, t_env **env,
		t_ms_state *status)
{
	t_cmd	*current;
	int		pid;

	current = *(pipeline->cmds);
	while (current)
	{
		here_doc(current, env, status);
		if (g_reset_cancel == 2)
			break ;
		pid = fork();
		if (pid < 0)
			return (perror("fork error"), free_pipe_ends(pipeline->pipe_ends,
					pipeline->num_cmds));
		if (pid == 0)
		{
			child_set_up();
			execute_child_pipeline(pipeline, current);
			exit(status->exit_status);
		}
		current = current->next;
	}
}

void	execute_pipeline(t_cmd **cmds, t_env **env, t_ms_state *status)
{
	t_pipeline			*pipeline;
	struct sigaction	ori_sigint;
	struct sigaction	ori_sigquit;

	pipeline = init_pipeline(cmds, env, status);
	save_original_signal(&ori_sigint, &ori_sigquit);
	ignore_signal();
	run_command_pipeline(pipeline, env, status);
	close_pipe_ends(pipeline->pipe_ends, pipeline->num_cmds);
	parent_wait(status);
	restore_original_signal(&ori_sigint, &ori_sigquit);
	free_pipe_ends(pipeline->pipe_ends, pipeline->num_cmds);
	free(pipeline);
}
