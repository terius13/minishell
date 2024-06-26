/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:58:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/26 15:42:20 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell_loop(t_cmd **cmds, t_env **env_dup, t_ms_state *status)
{
	int			i;
	char		*line;

	while (1)
	{
		rl_done = 0;
		line = readline(C "shell@st42:$ " RST);
		if (line == NULL)
			sigexit_handler(cmds, env_dup, status);
		i = 0;
		skip_wp(line, &i);
		if (line[i] == '\0')
			continue;
		add_history(line);
		if (lexer_and_parse(cmds, line, env_dup, status))
		{
			free_cmds(cmds);
			continue;
		}
        if ((*cmds)->next)
            execute_pipeline(cmds, env_dup, status);
        else
            do_single_cmd(cmds, env_dup, status);
		free_cmds(cmds);
	}
}

int	main(int ac, char **av, char **env)
{
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
	minishell_loop(cmds, env_dup, status);
	return (0);
}
