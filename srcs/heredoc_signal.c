/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:48:39 by ting              #+#    #+#             */
/*   Updated: 2024/06/28 18:49:03 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    here_doc_handler(int siggy)
{
    (void)siggy;
    g_reset_cancel = 2;
    if (isatty(STDIN_FILENO))
        ft_putstr_fd("\n", STDOUT_FILENO);
}

int here_doc_set_up(struct sigaction *old_sa)

{
    struct sigaction    here_doc;
    
    here_doc.sa_handler = here_doc_handler;
    sigemptyset(&here_doc.sa_mask);
    here_doc.sa_flags = 0;
    if (sigaction(SIGINT, &here_doc, old_sa) == -1)
    {
        perror("here_doc_ctrl_c");
        exit (EXIT_FAILURE);
    }
    return (0);
}