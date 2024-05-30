/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:33:57 by ting              #+#    #+#             */
/*   Updated: 2024/05/30 16:34:36 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*new_lexer(char *str)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, "<") ||!ft_strcmp(str, ">")
			|| !ft_strcmp(str, "<<") || !ft_strcmp(str, ">>"))
	{
		new->type = 1;
	}
	else
	{
		new->type = 2;
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

//add the splited lexer words to t_lexer
//set the next and prev
void	lexer_add_back(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*current;

	if (!lexer || !new)
		return ;
	if (!*lexer)
	{
		*lexer = new;
		new->prev = NULL;
		new->next = NULL;
	}
	else
	{
		current = *lexer;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new;
		new->prev = current;
		new->next = NULL;
	}
}
