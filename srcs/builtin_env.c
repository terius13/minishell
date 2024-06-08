/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:15:09 by asyed             #+#    #+#             */
/*   Updated: 2024/06/08 12:22:52 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_env **env_list)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current ->next;
	}
}

t_env	**env_error(char *message)

{
	perror (message);
	return (NULL);
}

void	create_copy(t_env **env_list, char *env)

{
	char	**split;
	char	*key;
	char	*value;
	t_env	*new_node;

	split = ft_split(env, '=');
	if (split == NULL || split[0] == NULL)
	{
		env_error("ft_split");
		return ;
	}
	key = ft_strdup(split[0]);
	if (split[1] != NULL)
		value = ft_strdup(split[1]);
	else
		value = NULL;
	if (key == NULL || (split[1] != NULL && value == NULL))
	{
		env_error("ft_strdup");
		return ;
	}
	new_node = ft_lstnew_ms(key, value);
	if (new_node == NULL)
	{
		env_error("ft_lstnew_ms");
		return ;
	}
	ft_lstadd_back_ms(env_list, new_node);
	free_array(split);
}

t_env	**init_env_copy(char **env)
{
	t_env	**env_list;
	int		i;

	i = 0;
	env_list = (t_env **)malloc(sizeof(t_env *));
	if (env_list == NULL)
		return (NULL);
	*env_list = NULL;
	while (env[i] != NULL)
	{
		create_copy(env_list, env[i]);
		i++;
	}
	return (env_list);
}
