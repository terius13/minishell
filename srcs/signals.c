/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:34:26 by asyed             #+#    #+#             */
/*   Updated: 2024/06/20 20:36:34 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigexit_handler(t_cmd **cmds, t_env **env_dup, t_ms_state *status)

{
	ft_putendl_fd("exit", STDOUT_FILENO); // Handle Ctrl + D
	rl_clear_history();
	free_all_and_exit(cmds, env_dup, status);
	exit(EXIT_SUCCESS); // EOF, Ctrl + D
}

void	sigignore_handler()
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler()

{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	signal_handlers_setup(void)
{
	struct sigaction	sa_ignore;
	struct sigaction	sa_quit;	
	
	sa_ignore.sa_handler = sigignore_handler;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	if (sigaction(SIGINT, &sa_ignore, NULL) == -1)
	{
		perror("SIGINT");
		return (1);
	}
	sa_quit.sa_handler = sigquit_handler;
	sigemptyset(&sa_ignore.sa_mask);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("SIGQUIT");
		return (1);
	}
	return (0);
}