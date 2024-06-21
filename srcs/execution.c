/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:10:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/21 17:15:20 by ting             ###   ########.fr       */
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
	int	exit_status;
	int	stat;

	if ((*cmds)->builtin)
		if (!ft_strcmp((*cmds)->cmd_arr[0], "cd")
			|| !ft_strcmp((*cmds)->cmd_arr[0], "export")
			|| !ft_strcmp((*cmds)->cmd_arr[0], "unset")
			|| !ft_strcmp((*cmds)->cmd_arr[0], "exit"))
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
			// have to free in child process before exit
		exit(stat);
	}
	waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		status->exit_status = WEXITSTATUS(exit_status);
}

int	cmds_len(t_cmd *cmds)
{
	t_cmd	*current;
	int 	num_cmds;

	num_cmds = 0;
	current = cmds;
	while (current)
    {
        num_cmds++;
        current = current->next;
    }
	return (num_cmds);
}

// Dynamically allocate memory for pipe_ends
int	**init_pipe_ends(int num_cmds)
{
	int		**pipe_ends;
	int		i;
	
	i = 0;
	pipe_ends = (int **)malloc(sizeof(int *) * (num_cmds - 1));
	if (!pipe_ends)
		return (perror("malloc error"), NULL);
	while (i < num_cmds - 1)
	{
		pipe_ends[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_ends[i])
			return (perror("malloc error"), NULL);
		i++;
	}
	return (pipe_ends);
}

void	init_pipes(int **pipe_ends, int num_cmds)
{
	int		i;
	int		j;
	
	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(pipe_ends[i]) == -1)
		{
			perror("pipe error");
			// Free allocated memory in case of error
			j = 0;
			while (j < num_cmds - 1)
			{
				free(pipe_ends[j]);
				j++;
			}
			free(pipe_ends);
			return  ;
		}
		i++;
	}
}

void	execute_pipeline(t_cmd **cmds, t_env **env, t_ms_state *status)
{
	int		num_cmds;
	t_cmd	*current;
	int		i;
	int		pid;
	int		exit_status;
	int		**pipe_ends;
	int		j;
	int	stat;

	num_cmds = cmds_len((*cmds));
	

	current = *cmds;
	i = 0;
	// if (!ft_strcmp(current->cmd_arr[0], "exit"))
	// {
	// 	return (execute_builtins(cmds, (*cmds)->cmd_arr, env, status));
	// }
	pipe_ends = init_pipe_ends(num_cmds);
	init_pipes(pipe_ends, num_cmds);
	while (current)
	{
		//if encounter any of the builtin unallowed, exit out of the process
		//so dont need to check here and execute anymore
		if (current->builtin && (!ft_strcmp(current->cmd_arr[0], "cd")
                || !ft_strcmp(current->cmd_arr[0], "export")
                || !ft_strcmp(current->cmd_arr[0], "unset")))
            //    || !ft_strcmp(current->cmd_arr[0], "exit")))
        {
            // Execute built-in commands directly in parent process
            execute_builtins(&current, current->cmd_arr, env, status);
            current = current->next;
            continue;
        }
		else if (!ft_strcmp(current->cmd_arr[0], "exit"))
		{
			i = 0;
			while (i++ < num_cmds - 1)
				free(pipe_ends[i]);
			free(pipe_ends);
			return (execute_builtins(cmds, (*cmds)->cmd_arr, env, status));
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			// Free allocated memory in case of error
			j = 0;
			while (j < num_cmds - 1)
			{
				free(pipe_ends[j]);
				j++;
			}
			free(pipe_ends);
			return ;
		}
		if (pid == 0)
		{
			if (i > 0)
			{
				dup2(pipe_ends[i - 1][0], STDIN_FILENO);
			}
			if (i < num_cmds - 1)
			{
				dup2(pipe_ends[i][1], STDOUT_FILENO);
			}
			j = 0;
			while (j < num_cmds - 1)
			{
				close(pipe_ends[j][0]);
				close(pipe_ends[j][1]);
				j++;
			}
			do_redirection(current, status);
			//check if builtin is unallowed, exit out of child process
			//only execute builtins if its allowed
			if (current->builtin)
				execute_builtins(&current, current->cmd_arr, env, status);
			else
				execute_cmd(current, env, status);
			stat = status->exit_status;
			free_all_and_exit(cmds, env, status);
			while (i++ < num_cmds - 1)
				free(pipe_ends[i]);
			free(pipe_ends);
			exit(stat);
		}
		current = current->next;
		i++;
	}

	i = 0;
	while (i < num_cmds - 1)
	{
		close(pipe_ends[i][0]);
		close(pipe_ends[i][1]);
		i++;
	}

	i = 0;
	exit_status = 0;
	while (i < num_cmds)
	{
		wait(&exit_status);
		if (WIFEXITED(exit_status))
			status->exit_status = WEXITSTATUS(exit_status);
		i++;
	}

	// Free allocated memory
	i = 0;
	while (i < num_cmds - 1)
	{
		free(pipe_ends[i]);
		i++;
	}
	free(pipe_ends);
}
