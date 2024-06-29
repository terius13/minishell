/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:48:39 by ting              #+#    #+#             */
/*   Updated: 2024/06/29 21:24:55 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_reset_cancel;

void    here_doc_handler(int siggy)
{
    (void)siggy;

    g_reset_cancel = 2;
    // if (isatty(STDIN_FILENO))
    ft_putstr_fd("\n", STDOUT_FILENO);
    ft_putstr_fd("here_doc handler activate\n", STDOUT_FILENO);
}

int here_doc_set_up(struct sigaction *old_quit, struct sigaction *old_ign)

{
    struct sigaction    here_doc;
    struct sigaction    do_nothing;
    
    here_doc.sa_handler = here_doc_handler;
    sigemptyset(&here_doc.sa_mask);
    here_doc.sa_flags = 0;
    if (sigaction(SIGINT, &here_doc, old_quit) == -1)
    {
        perror("here_doc_ctrl_c");
        exit (EXIT_FAILURE);
    }
    do_nothing.sa_handler = SIG_IGN;
	sigemptyset(&do_nothing.sa_mask);
	do_nothing.sa_flags = 0;
	if (sigaction(SIGQUIT, &do_nothing, old_ign) == -1)
	{
		perror("Ctrl-\\");
		exit (EXIT_FAILURE);
	}
    return (0);
}
