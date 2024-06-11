/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_node_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:46:41 by asyed             #+#    #+#             */
/*   Updated: 2024/06/11 14:46:51 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_new_env_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	(*new).key = key;
	(*new).value = value;
	(*new).next = NULL;
	return (new);
}

void	ft__add_env_back_node(t_env **lst, t_env *new)
{
	t_env	*current;

	current = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current->next)
	{
		current = current->next;
	}
	current->next = new;
}

