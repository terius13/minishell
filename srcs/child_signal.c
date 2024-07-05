/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:16:24 by asyed             #+#    #+#             */
/*   Updated: 2024/07/05 15:22:33 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_reset_cancel;

void	child_handler(int siggy)
{
	(void)siggy;
	g_reset_cancel = 3;
}

void	save_original_signal(struct sigaction *ori_sigint,
		struct sigaction *ori_sigquit)
{
	sigaction(SIGINT, NULL, ori_sigint);
	sigaction(SIGQUIT, NULL, ori_sigquit);
}

void	restore_original_signal(struct sigaction *ori_sigint,
		struct sigaction *ori_sigquit)
{
	sigaction(SIGINT, ori_sigint, NULL);
	sigaction(SIGQUIT, ori_sigquit, NULL);
}

void	ignore_signal(void)
{
	struct sigaction	ignore;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGINT, &ignore, NULL);
	sigaction(SIGQUIT, &ignore, NULL);
}

void	child_set_up(void)
{
	struct sigaction	child;
	struct sigaction	dump;

	child.sa_handler = SIG_DFL;
	child.sa_flags = 0;
	sigemptyset(&child.sa_mask);
	if (sigaction(SIGINT, &child, NULL) == -1)
	{
		perror("child_ctrl_c");
		exit(EXIT_FAILURE);
	}
	dump.sa_handler = SIG_DFL;
	sigemptyset(&dump.sa_mask);
	dump.sa_flags = 0;
	if (sigaction(SIGQUIT, &dump, NULL) == -1)
	{
		perror("Ctrl-\\");
		exit(EXIT_FAILURE);
	}
}
