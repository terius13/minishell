/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:58:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/08 13:07:08 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_lexer **lexer;
	t_cmd	**cmds;
	t_env	**env_dup;
	t_cmd	*current;

	(void)ac;
	(void)av;
	env_dup = init_env_copy(env);
	if (env_dup == NULL)
	{
		perror ("init_env_copy");
		return (1);
	}
	lexer = (t_lexer **)malloc(sizeof(t_lexer *));
	*lexer = NULL;
	cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	*cmds = NULL;
	while (1)
	{
		line = readline(C "shell@st42:$ " RST);
		if (line == NULL)
			break ; // exit if EOF or error, can be Ctrl + D
		if (line)
		{
			lexical_analysis(lexer, line);
			free(line);
			printf("After lexer:\n");
			print_lexer(lexer);
			parsing(lexer, cmds);
			print_parse(cmds);
			free_lexer(lexer);
			current = *cmds;
			while(current)
			{
				if (current->builtin)
					execute_builtins(current->cmd_arr, env_dup);
				current = current->next;
			}
			free_cmds(cmds);
		//	freeall_and_exit(lexer, cmds ,line); //should be in exit func
		}
	}
	return (0);
}
