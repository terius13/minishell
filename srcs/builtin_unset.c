/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:23:39 by asyed             #+#    #+#             */
/*   Updated: 2024/07/04 14:43:56 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_unset_node(t_env *del)
{
	if (del)
	{
		if (del->key)
			free(del->key);
		if (del->value)
			free(del->value);
		free(del);
	}
}

int	builtin_unset(char **args, t_env **env_list)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 0;
	while (args[++i])
	{
		tmp = *env_list;
		prev = NULL;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, args[i]) == 0)
			{
				if (prev)
					prev->next = tmp->next;
				else
					*env_list = tmp->next;
				free_unset_node(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (0);
}
