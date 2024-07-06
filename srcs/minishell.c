/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:58:54 by ting              #+#    #+#             */
/*   Updated: 2024/07/06 12:26:17 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_reset_cancel = 0;

void	print_error(char *str)
{
	printf("shell@st42: %s\n", str);
}

void	execution(t_cmd **cmds, t_env **env_dup, t_ms_state *status)
{
	update_underscoreequal(env_dup, cmds);
	if ((*cmds)->next)
		execute_pipeline(cmds, env_dup, status);
	else
		do_single_cmd(cmds, env_dup, status);
	free_cmds(cmds);
	if (access(".hdc.tmp", F_OK) != -1)
	{
		if (unlink(".hdc.tmp") == -1)
			perror("unlink");
	}
}

char	*readline_and_signal(t_cmd **cmds, t_env **env_dup, t_ms_state *status)
{
	char				*line;
	struct sigaction	old_sa;

	if (sigaction(SIGINT, NULL, &old_sa) == -1)
		exit(EXIT_FAILURE);
	line = readline(C "shell@st42:$ " RST);
	if (sigaction(SIGINT, &old_sa, NULL) == -1)
		exit(EXIT_FAILURE);
	if (line == NULL)
		sigexit_handler(cmds, env_dup, status);
	return (line);
}

int	update_exitreset_status(t_ms_state *status)
{
	if (g_reset_cancel == 1 || g_reset_cancel == 2 || g_reset_cancel == 3)
	{
		status->exit_status = 130;
		g_reset_cancel = 0;
		return (1);
	}
	return (0);
}

void	minishell_loop(t_cmd **cmds, t_env **env_dup, t_ms_state *status)
{
	int		i;
	char	*line;

	while (1)
	{
		if (update_exitreset_status(status))
			continue ;
		line = readline_and_signal(cmds, env_dup, status);
		update_exitreset_status(status);
		i = 0;
		skip_wp(line, &i);
		if (line[i] == '\0')
			continue ;
		add_history(line);
		if (lexer_and_parse(cmds, line, env_dup, status))
		{
			free_cmds(cmds);
			continue ;
		}
		execution(cmds, env_dup, status);
	}
}
