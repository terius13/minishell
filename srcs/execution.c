/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:10:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/22 21:57:40 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// pipefd[0] is for reading end
// pipefd[1] is for writing end

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

	if ((*cmds)->builtin && (!ft_strcmp((*cmds)->cmd_arr[0], "cd")
		|| !ft_strcmp((*cmds)->cmd_arr[0], "export")
		|| !ft_strcmp((*cmds)->cmd_arr[0], "unset")
		|| !ft_strcmp((*cmds)->cmd_arr[0], "exit")))
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
	parent_wait(status);
}

void	execute_pipeline(t_cmd **cmds, t_env **env, t_ms_state *status)
{
	int		num_cmds;
	t_cmd	*current;
	int		i;
	int		pid;
	int		**pipe_ends;
	int		stat;

	num_cmds = cmds_len((*cmds));
	current = *cmds;
	i = 0;
	pipe_ends = init_pipe_ends(num_cmds);
	init_pipes(pipe_ends, num_cmds);
	while (current)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			free_pipe_ends(pipe_ends, num_cmds);
			return ;
		}
		if (pid == 0)
		{
			if (i > 0)
				dup2(pipe_ends[i - 1][0], STDIN_FILENO);
			if (i < num_cmds - 1)
				dup2(pipe_ends[i][1], STDOUT_FILENO);
			close_pipe_ends(pipe_ends, num_cmds);
			do_redirection(current, status);
			if (current->builtin && (!ft_strcmp(current->cmd_arr[0], "cd")
                || !ft_strcmp(current->cmd_arr[0], "export")
                || !ft_strcmp(current->cmd_arr[0], "unset")
                || !ft_strcmp(current->cmd_arr[0], "exit")))
        	{
				free_all_and_exit(cmds, env, status);
				free_pipe_ends(pipe_ends, num_cmds);
				exit(0);
        	}
			if (current->builtin)
				execute_builtins(&current, current->cmd_arr, env, status);
			else
				execute_cmd(current, env, status);
			stat = status->exit_status;
			free_all_and_exit(cmds, env, status);
			free_pipe_ends(pipe_ends, num_cmds);
			exit(stat);
		}
		current = current->next;
		i++;
	}
	close_pipe_ends(pipe_ends, num_cmds);
	i = 0;
	while (i++ < num_cmds)
		parent_wait(status);
	free_pipe_ends(pipe_ends, num_cmds);
}
