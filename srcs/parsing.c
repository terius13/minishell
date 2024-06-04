/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:22:50 by ting              #+#    #+#             */
/*   Updated: 2024/06/04 11:48:54 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//split on pipes
//then remove quotes
//store it in an array **cmd

void	parsing(t_lexer **lexer, t_cmd **cmds)
{
	int		i;

	while (*lexer)
	{
		if (ft_strcmp(current->str, '|'))
		{
			(*cmds)->cmd_arr[i] = current->str;
		}
		else if (!ft_strcmp(current->str, '|'))
		{
			current = current->next;
		}
		current = current->next;
	}
}

