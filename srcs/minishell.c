/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:58:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/04 13:36:05 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*int	main(int argc, char **argv, char **env)
{
	while (1)
	{
		readline(C "shell@st42:$ " RST);
	}
	return (0);
}
*/

int	main(void)
{
	char	*line;
	t_lexer **lexer;
	t_cmd	**cmds;

	lexer = (t_lexer **)malloc(sizeof(t_lexer *));
	*lexer = NULL;
	cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	*cmds = NULL;
	while (1)
	{
		line = readline(C "shell@st42:$ " RST);
		if (line)
		{
			lexical_analysis(lexer, line);
			printf("After lexer:\n");
			print_lexer(lexer);
			parsing(lexer, cmds);
			printf("entering free all\n");
			free_cmds(cmds);
			free_all(lexer, line);
		}
	}
	return (0);
}
