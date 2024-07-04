/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:53:54 by ting              #+#    #+#             */
/*   Updated: 2024/07/04 11:24:15 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Type 1:string, type 2:'|', type 3:'<'
// Type 4:'>', Type 5:'<<', type 6:'>>'
t_lexer	*new_lexer(char *str)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!ft_strcmp(str, "|"))
		new->type = 2;
	else if (!ft_strcmp(str, "<"))
		new->type = 3;
	else if (!ft_strcmp(str, ">"))
		new->type = 4;
	else if (!ft_strcmp(str, "<<"))
		new->type = 5;
	else if (!ft_strcmp(str, ">>"))
		new->type = 6;
	else
		new->type = 1;
	new->next = NULL;
	new->prev = NULL;
	free(str);
	return (new);
}

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
			current = current->next;
		current->next = new;
		new->prev = current;
		new->next = NULL;
	}
}

void	del_lexer(t_lexer **lexer, t_lexer *to_del)
{
	if (to_del->prev)
		to_del->prev->next = to_del->next;
	else
		*lexer = to_del->next;
	if (to_del->next)
		to_del->next->prev = to_del->prev;
	free(to_del->str);
	free(to_del);
}

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}
