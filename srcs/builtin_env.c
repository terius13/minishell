/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:15:09 by asyed             #+#    #+#             */
/*   Updated: 2024/06/20 11:36:27 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_env(t_env **env_list, char *to_find)

{
	t_env *current;

	current = *env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, to_find) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int		builtin_env(t_env **env_list, char **args)
{
	t_env	*current;
	int ac;

	ac = 0;
	while (args[ac])
		ac++;
	if (ac > 1)
	{
		print_error("No such file or directory");
		return (1);
	}
	current = *env_list;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current ->next;
	}
	return (0);
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
	new_node = ft_new_env_node(key, value);
	if (new_node == NULL)
	{
		env_error("ft_lstnew_ms");
		return ;
	}
	ft_add_env_back_node(env_list, new_node);
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
