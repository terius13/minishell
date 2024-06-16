/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:58:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/15 18:07:24 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	main(int ac, char **av, char **env)
{
	char		*line;
	t_cmd		**cmds;
	t_env		**env_dup;
	t_cmd		*current;
	t_ms_state	*update;

	(void)ac;
	(void)av;

	update = (t_ms_state *)malloc(sizeof(t_ms_state));
	if (update == NULL)
	{
		perror ("init_env_copy");
		return (1);
	}
	update->exit_status = 0;
	env_dup = init_env_copy(env);
	if (env_dup == NULL)
	{
		perror ("init_env_copy");
		free(update);
		return (1);
	}
	cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	*cmds = NULL;
	while (1)
	{
		line = readline(C "shell@st42:$ " RST);
		if (line == NULL)
		{
			rl_clear_history();
			break ; // exit if EOF or error, can be Ctrl + D
		}
		if (line && *line)
		{
			add_history(line);
			if (lexer_and_parse(cmds, line, env_dup))
			{
				free_cmds(cmds);
				free(line); //prob dont need to free, only in exit
				continue;
			}
			free(line);
			current = *cmds;
			while(current)
			{
				if (current->builtin)
					update->exit_status = execute_builtins(cmds, current->cmd_arr, env_dup, update);
				current = current->next;
			}
			free_cmds(cmds);
		}
	}
	rl_clear_history();
	return (update->exit_status);
}
