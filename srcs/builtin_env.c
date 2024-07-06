/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:15:09 by asyed             #+#    #+#             */
/*   Updated: 2024/07/06 12:26:09 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_env(t_env **env_list, char *to_find)
{
	t_env	*current;

	current = *env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, to_find) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	builtin_env(t_env **env_list, char **args)
{
	t_env	*current;
	int		ac;

	ac = 0;
	while (args[ac])
		ac++;
	if (ac > 1)
	{
		print_error("No such file or directory");
		return (127);
	}
	current = *env_list;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

void	create_copy(t_env **env_list, char *env)
{
	char	**split;
	char	*key;
	char	*value;
	t_env	*new_node;

	split = ft_split(env, '=');
	if (split == NULL || split[0] == NULL)
		return ;
	key = ft_strdup(split[0]);
	if (split[1] != NULL)
		value = ft_strdup(split[1]);
	else
		value = NULL;
	if (key == NULL || (split[1] != NULL && value == NULL))
		return ;
	new_node = ft_new_env_node(key, value);
	if (new_node == NULL)
		return ;
	ft_add_env_back_node(env_list, new_node);
	free_array(split);
}

void	update_underscoreequal(t_env **env_list, t_cmd **cmds)
{
	t_env	*current;
	int		i;

	i = 0;
	current = *env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "_") == 0)
		{
			if (current->value != NULL)
			{
				free(current->value);
				current->value = NULL;
			}
			while ((*cmds)->cmd_arr[i])
				i++;
			if (ft_strcmp("env", (*cmds)->cmd_arr[i - 1]) == 0)
				current->value = ft_strjoin("usr/bin/", (*cmds)->cmd_arr[i
						- 1]);
			else
				current->value = ft_strdup((*cmds)->cmd_arr[i - 1]);
			return ;
		}
		current = current->next;
	}
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
