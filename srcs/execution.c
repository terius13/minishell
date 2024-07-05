/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:10:54 by ting              #+#    #+#             */
/*   Updated: 2024/07/05 18:23:53 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ft_putstr_fd(cmd->cmd_arr[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		status->exit_status = 127;
	}
}

void	single_cmd_parent(int pid, t_ms_state *status)
{
	struct sigaction	ori_sigint;
	struct sigaction	ori_sigquit;
	int					exit_status;

	save_original_signal(&ori_sigint, &ori_sigquit);
	ignore_signal();
	waitpid(pid, &exit_status, 0);
	restore_original_signal(&ori_sigint, &ori_sigquit);
	if (WIFEXITED(exit_status))
		status->exit_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (WTERMSIG(exit_status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		status->exit_status = 128 + WTERMSIG(exit_status);
	}
}

void	do_single_cmd(t_cmd **cmds, t_env **env, t_ms_state *status)
{
	int	pid;

	if (illegal_builtins((*cmds)))
		return (execute_builtins(cmds, (*cmds)->cmd_arr, env, status));
	here_doc((*cmds), env, status);
	if (g_reset_cancel == 2)
		return ;
	pid = fork();
	if (pid < 0)
		return (perror("fork error"));
	if (pid == 0)
	{
		child_set_up();
		execute_child_single_cmd(cmds, env, status);
	}
	else
		single_cmd_parent(pid, status);
}

void	execute_child_single_cmd(t_cmd **cmds, t_env **env, t_ms_state *status)
{
	int	stat;

	do_redirection((*cmds), status);
	if ((*cmds)->builtin)
		execute_builtins(cmds, (*cmds)->cmd_arr, env, status);
	else if ((*cmds)->cmd_arr[0])
		execute_cmd((*cmds), env, status);
	stat = status->exit_status;
	free_all_and_exit(cmds, env, status);
	exit(stat);
}
