/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_node_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:46:41 by asyed             #+#    #+#             */
/*   Updated: 2024/05/31 16:31:17 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstiter_ms(t_env *lst, void (*f)(void *))
{
	int	i;

	i = 0;
	while (lst)
	{	
		if (lst == NULL)
		{
			printf("lst id NULL");
			break;
		}
		(*f)(lst);
		lst = lst->next;
		printf("print success %d\n", i++);
	}
	printf("print SUCCESS");
}

t_env	*ft_lstnew_ms(char *key, char *value)
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

void	ft_lstadd_back_ms(t_env **lst, t_env *new)
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

void	ft_lstclear_ms(t_env **lst, void (*del)(void *))
{
	t_env	*head;

	while (*lst)
	{
		head = (**lst).next;
		del((**lst).key);
		del((**lst).value);
		free(*lst);
		*lst = head;
	}
	*lst = NULL;
}
