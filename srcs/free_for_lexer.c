/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_for_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:56:44 by ting              #+#    #+#             */
/*   Updated: 2024/05/31 17:04:19 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_lexer(t_lexer **lexer)
{
    t_lexer *current;
    t_lexer *next;

    if (!lexer || !*lexer)
        return;
    current = *lexer;
    while (current)
	{
        next = current->next;
        free(current->str);
        free(current);
        current = next;
    }
    *lexer = NULL;
}

void	free_all(t_lexer **lexer, char *line)
{
	if (*lexer)
		free_lexer(lexer);
	if (lexer)
		free(lexer);
	if (line)
		free(line);
	exit(1); //need to exit so the func that called this with error dont continue running
}