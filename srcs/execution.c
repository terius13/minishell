/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:10:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/29 20:34:05 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_reset_cancel;

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

void do_single_cmd(t_cmd **cmds, t_env **env, t_ms_state *status)
{
    int pid;
    int exit_status;
    struct sigaction ignore, orig_sigint, orig_sigquit;

    if (illegal_builtins((*cmds)))
        return (execute_builtins(cmds, (*cmds)->cmd_arr, env, status));

    here_doc((*cmds), env, status);
    pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        return;
    }
    if (pid == 0) // Child process
    {
        // Restore default signal handling in the child process
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        execute_child_single_cmd(cmds, env, status);
    }
    else // Parent process
    {
        // Save the original signal handler for SIGINT and SIGQUIT
        sigaction(SIGINT, NULL, &orig_sigint);
        sigaction(SIGQUIT, NULL, &orig_sigquit);

        // Ignore SIGINT and SIGQUIT in the parent while waiting for the child
        ignore.sa_handler = SIG_IGN;
        sigemptyset(&ignore.sa_mask);
        ignore.sa_flags = 0;
        sigaction(SIGINT, &ignore, NULL);
        sigaction(SIGQUIT, &ignore, NULL);

        waitpid(pid, &exit_status, 0);

        // Restore the original signal handler for SIGINT and SIGQUIT in the parent
        sigaction(SIGINT, &orig_sigint, NULL);
        sigaction(SIGQUIT, &orig_sigquit, NULL);

        if (WIFEXITED(exit_status))
        {
            status->exit_status = WEXITSTATUS(exit_status);
        }
        else if (WIFSIGNALED(exit_status))
        {
            // If the child was terminated by SIGINT or SIGQUIT, print appropriate message
            if (WTERMSIG(exit_status) == SIGINT)
            {
                ft_putstr_fd("\n", STDOUT_FILENO);
            }
            else if (WTERMSIG(exit_status) == SIGQUIT)
            {
                ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
            }
            status->exit_status = 128 + WTERMSIG(exit_status);
        }
    }
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

void	execute_child_pipeline(t_pipeline *pipeline, t_cmd *current, int i)
{
	init_dup(pipeline->num_cmds, i, pipeline->pipe_ends);
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
