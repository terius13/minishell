/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:16:24 by asyed             #+#    #+#             */
/*   Updated: 2024/07/01 15:45:17 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_reset_cancel;

void    child_handler(int siggy)
{	
	(void)siggy;
	
    ft_putstr_fd("\n", STDOUT_FILENO);
    // ft_putstr_fd("child handler activate", STDOUT_FILENO);
    
// 	if (isatty(STDIN_FILENO))
// 	{
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
 	g_reset_cancel = 3;
}

void    save_original_signal(struct sigaction *ori_sigint, struct sigaction *ori_sigquit)
{
    sigaction(SIGINT, NULL, ori_sigint);
    sigaction(SIGQUIT, NULL, ori_sigquit);
}

void    restore_original_signal(struct sigaction *ori_sigint, struct sigaction *ori_sigquit)
{
    sigaction(SIGINT, ori_sigint, NULL);
    sigaction(SIGQUIT, ori_sigquit, NULL);
}

void    ignore_signal(void)
{
    struct sigaction	ignore;
    
    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    sigaction(SIGINT, &ignore, NULL);
    sigaction(SIGQUIT, &ignore, NULL);
}
void    child_set_up()
{
    struct sigaction    child;
    struct sigaction    dump;
    
    child.sa_handler = SIG_DFL;
    child.sa_flags = 0;
    sigemptyset(&child.sa_mask);
    if (sigaction(SIGINT, &child, NULL) == -1)
    {
        perror("child_ctrl_c");
        exit (EXIT_FAILURE);
    }
    ft_putstr_fd("child set_up activate\n", STDOUT_FILENO);
    
    dump.sa_handler = SIG_DFL;
	sigemptyset(&dump.sa_mask);
	dump.sa_flags = 0;
	if (sigaction(SIGQUIT, &dump, NULL) == -1)
	{
		perror("Ctrl-\\");
		exit (EXIT_FAILURE);
	}
    ft_putstr_fd("dump child set_up activate\n", STDOUT_FILENO);
}
