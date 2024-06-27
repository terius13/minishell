/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:10:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/27 15:59:29 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	illegal_builtins(t_cmd *current)
{
	if (current->builtin && (!ft_strcmp(current->cmd_arr[0], "cd")
			|| !ft_strcmp(current->cmd_arr[0], "export")
			|| !ft_strcmp(current->cmd_arr[0], "unset")
			|| !ft_strcmp(current->cmd_arr[0], "exit")))
	{
		return (1);
	}
	return (0);
}

void	free_n_exit_child(t_pipeline *pipeline)
{
	int	stat;
	int	num_cmds;

	num_cmds = cmds_len((*pipeline->cmds));
	stat = pipeline->status->exit_status;
	free_all_and_exit(pipeline->cmds, pipeline->env, pipeline->status);
	free_pipe_ends(pipeline->pipe_ends, num_cmds);
	free(pipeline);
	exit(stat);
}

void	execute_cmd(t_cmd *cmd, t_env **env, t_ms_state *status)
{
	char	*cmd_path;

	cmd_path = find_path(cmd->cmd_arr[0], env);
	if (cmd_path)
	{
		execve(cmd_path, cmd->cmd_arr, env_in_arr(env));
		free(cmd_path);
	}
	else
	{
		printf("%s: command not found\n", cmd->cmd_arr[0]);
		status->exit_status = 127;
	}
}

void	do_single_cmd(t_cmd **cmds, t_env **env, t_ms_state *status)
{
	int	pid;
	int	stat;
	int	exit_status;

	if (illegal_builtins((*cmds)))
		return (execute_builtins(cmds, (*cmds)->cmd_arr, env, status));
	pid = fork();
	if (pid < 0)
		perror("fork error");
	if (pid == 0)
	{
		do_redirection((*cmds), status);
		if ((*cmds)->builtin)
			execute_builtins(cmds, (*cmds)->cmd_arr, env, status);
		else
			execute_cmd((*cmds), env, status);
		stat = status->exit_status;
		free_all_and_exit(cmds, env, status);
		exit(stat);
	}
	wait(&exit_status);
	if (WIFEXITED(exit_status))
		status->exit_status = WEXITSTATUS(exit_status);
}

void	execute_child_process(t_pipeline *pipeline, t_cmd *current, int i)
{
	init_dup(pipeline->num_cmds, i, pipeline->pipe_ends);
	do_redirection(current, pipeline->status);
	if (illegal_builtins(current))
		free_n_exit_child(pipeline);
	if (current->builtin)
		execute_builtins(&current, current->cmd_arr, pipeline->env,
			pipeline->status);
	else
		execute_cmd(current, pipeline->env, pipeline->status);
	free_n_exit_child(pipeline);
}
