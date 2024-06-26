/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:34:26 by asyed             #+#    #+#             */
/*   Updated: 2024/06/26 19:45:44 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_reset_cancel;

void	sigexit_handler(t_cmd **cmds, t_env **env_dup, t_ms_state *status)

{
	ft_putendl_fd("exit", STDOUT_FILENO); // Handle Ctrl + D
	rl_clear_history();
	free_all_and_exit(cmds, env_dup, status);
	exit(EXIT_SUCCESS); // EOF, Ctrl + D
}

void	cancel_handler()

{
	if (isatty(STDIN_FILENO))
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_reset_cancel = 1;
}

int	signal_handlers_setup(void)
{
	struct sigaction	do_nothing;
	struct sigaction	cancel;	
	
	do_nothing.sa_handler = SIG_IGN;
	sigemptyset(&do_nothing.sa_mask);
	do_nothing.sa_flags = 0;
	if (sigaction(SIGQUIT, &do_nothing, NULL) == -1)
	{
		perror("Ctrl-\\");
		return (1);
	}
	cancel.sa_handler = cancel_handler;
	sigemptyset(&cancel.sa_mask);
	cancel.sa_flags = 0;
	if (sigaction(SIGINT, &cancel, NULL) == -1)
	{
		perror("Ctrl-C");
		return (1);
	}
	return (0);
}
