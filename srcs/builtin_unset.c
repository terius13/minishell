/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:23:39 by asyed             #+#    #+#             */
/*   Updated: 2024/06/01 20:24:53 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_unset(t_env **env_list, char *var)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env_list;
	prev = NULL;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, var) == 0)
		{
			if (prev != NULL)
				prev->next = tmp->next;
			else
				*env_list = tmp->next;
			free_unset_env(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	free_unset_env(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}
