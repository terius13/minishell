/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:10:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/20 12:20:38 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	handle_cmd(t_cmd **cmds, t_cmd *current, t_env **env, t_ms_state *status)
// {
// 	do_redirection(current, status);
// 	if (current->builtin)
// 	{
// 		execute_builtins(cmds, current->cmd_arr, env, status);
// 	}
// 	// else
// 	// {
// 	// 	//execve
// 	// }
// }


//pipefd[0] is for reading end
//pipefd[1] is for writing end
// int	execution(t_cmd **cmds, t_env **env, t_ms_state *status)
// {
// 	t_cmd	*current;
// 	int		pipefd[2];
// 	int		pid;

// 	current = *cmds;
// 	while (current)
// 	{
// 		if (current->next)
// 			pipe(pipefd);
// 		pid = fork();
// 		if (pid < 0)
// 			perror("fork error");
// 		if (pid == 0)
// 		{
// 			dup2(pipefd[0], STDIN_FILENO);
// 			close(pipefd[0]);
// 			dup2(pipefd[1], STDOUT_FILENO);
// 			close(pipefd[1]);
// 			handle_cmd(cmds, current, env, status);
// 		}
// 		current = current->next;
// 	}
// 	waitpid(pid, NULL, 0);
// 	return (0);
// }

void	exec_single_cmd(t_cmd **cmds, t_env **env, t_ms_state *status)
{
	int		pid;
	int		exit_status;
	int		stat;

	//should execute the builtin and return, so no forking
	if ((*cmds)->builtin)
	{
		if (!ft_strcmp((*cmds)->cmd_arr[0], "cd") || !ft_strcmp((*cmds)->cmd_arr[0], "export")
			|| !ft_strcmp((*cmds)->cmd_arr[0], "unset") || !ft_strcmp((*cmds)->cmd_arr[0], "exit"))
		{
			execute_builtins(cmds, (*cmds)->cmd_arr, env, status);
			return;
		}
	}
	pid = fork();
	if (pid < 0)
		perror("fork error");
	if (pid == 0)
	{
		do_redirection((*cmds), status);
		if ((*cmds)->builtin)
		{
			execute_builtins(cmds, (*cmds)->cmd_arr, env, status);
			stat = status->exit_status;
			free_all_and_exit(cmds, env, status); //have to free in child process before exit
			exit(stat);
		}
		// else
		// {
		// 	//execve
		// }
		free_all_and_exit(cmds, env, status); //have to free in child process before exit
		exit(0);
	}
	waitpid(pid, &exit_status, 0);
    if (WIFEXITED(exit_status))
    {
        status->exit_status = WEXITSTATUS(exit_status);
    }
	
}
