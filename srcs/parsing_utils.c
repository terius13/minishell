/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:33:55 by ting              #+#    #+#             */
/*   Updated: 2024/07/04 11:47:03 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*new_cmd(char **arr)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd_arr = arr;
	new->in_pid = 0;
	new->out_pid = 1;
	new->infile = NULL;
	new->outfile = NULL;
	new->builtin = 0;
	new->append_re = NULL;
	new->hdoc_delimeter = NULL;
	new->next = NULL;
	return (new);
}

void	cmd_add_back(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*current;

	if (!cmds || !new)
		return ;
	if (!*cmds)
	{
		*cmds = new;
		new->next = NULL;
	}
	else
	{
		current = *cmds;
		while (current->next)
			current = current->next;
		current->next = new;
		new->next = NULL;
	}
}

int	cal_arg_count(t_lexer *curr_l)
{
	int	arg_count;

	arg_count = 0;
	while (curr_l && curr_l->type != 2)
	{
		arg_count++;
		curr_l = curr_l->next;
	}
	return (arg_count);
}

int	get_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

void	add_to_arr(char ***arr, char *str)
{
	int	size;

	size = get_arr_size(*arr);
	*arr = (char **)ft_realloc(*arr, size * sizeof(char *), (size + 2)
			* sizeof(char *));
	(*arr)[size] = ft_strdup(str);
	(*arr)[size + 1] = NULL;
}
