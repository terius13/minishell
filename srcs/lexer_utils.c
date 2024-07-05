/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:53:54 by ting              #+#    #+#             */
/*   Updated: 2024/07/05 20:03:31 by asyed            ###   ########.fr       */
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

void	check_builtins(t_cmd **cmds)
{
	t_cmd	*current;

	current = *cmds;
	while (current)
	{
		if (current->cmd_arr && current->cmd_arr[0]
			&& (!ft_strcmp(current->cmd_arr[0], "echo")
				|| !ft_strcmp(current->cmd_arr[0], "cd")
				|| !ft_strcmp(current->cmd_arr[0], "pwd")
				|| !ft_strcmp(current->cmd_arr[0], "export")
				|| !ft_strcmp(current->cmd_arr[0], "unset")
				|| !ft_strcmp(current->cmd_arr[0], "env")
				|| !ft_strcmp(current->cmd_arr[0], "exit")))
		{
			current->builtin = 1;
		}
		current = current->next;
	}
}
