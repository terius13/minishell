/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:48:39 by ting              #+#    #+#             */
/*   Updated: 2024/07/01 17:42:15 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_reset_cancel;

void	here_doc_handler(int siggy)
{
	(void)siggy;
	g_reset_cancel = 2;
    // rl_done = 1;
	// if (isatty(STDIN_FILENO))
	// ft_putstr_fd("\n", STDOUT_FILENO);
	// ft_putstr_fd("here_doc handler activate\n", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	// ft_putstr_fd("here_doc handler activate\n", STDOUT_FILENO);
}

void	here_doc_set_up(void)

{
	struct sigaction here_doc;
	struct sigaction ign;

	ign.sa_handler = SIG_IGN;
    // signal(SIGQUIT, SIG_DFL);
    ign.sa_flags = 0;
	sigemptyset(&ign.sa_mask);

	if (sigaction(SIGQUIT, &ign, NULL) == -1)
	{
		perror("Ctrl-\\");
		exit(EXIT_FAILURE);
    }
	here_doc.sa_handler = here_doc_handler;
    here_doc.sa_flags = 0;
	sigemptyset(&here_doc.sa_mask);

	if (sigaction(SIGINT, &here_doc, NULL) == -1)
	{
		perror("here_doc_ctrl_c");
		exit(EXIT_FAILURE);
	}
}
