/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:58:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/24 20:17:19 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_cmd		**cmds;
	t_env		**env_dup;
	t_ms_state	*status;

	(void)ac;
	(void)av;
	if (signal_handlers_setup() != 0)
		return (1);
	status = init_status();
	env_dup = init_envdup(status, env);
	cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	*cmds = NULL;
	while (1)
	{
		line = readline(C "shell@st42:$ " RST);
		if (line == NULL)
			sigexit_handler(cmds, env_dup, status);
		if (line && *line)
		{
			add_history(line);
			if (lexer_and_parse(cmds, line, env_dup, status))
			{
				free_cmds(cmds);
				free(line); //prob dont need to free, only in exit
				continue;
			}
			free(line);
            if ((*cmds)->next)
               execute_pipeline(cmds, env_dup, status);
            else
               do_single_cmd(cmds, env_dup, status);
			free_cmds(cmds);
		}
	}
}

