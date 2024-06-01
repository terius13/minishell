/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:58:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/01 16:03:53 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int	main(int argc, char **argv, char **env)
{
	while (1)
	{
		readline(C "shell@st42:$ " RST);
	}
	return (0);
}
*/

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_lexer **lexer;

	lexer = (t_lexer **)malloc(sizeof(t_lexer *));
	*lexer = NULL;
	while (1)
	{
		line = readline(C "shell@st42:$ " RST);
		if (line)
		{
			lexical_analysis(lexer, line);
			printf("After lexer:\n");
			print_lexer(lexer);
			free_all(lexer, line);
		}
	}
	return (0);
}
