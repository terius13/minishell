/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:15:09 by asyed             #+#    #+#             */
/*   Updated: 2024/06/02 16:05:44 by asyed            ###   ########.fr       */
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

t_env	**init_env_copy(char **env)
{
	t_env	**env_list;
	char	**split;
	int		i;

	i = 0;
	env_list = (t_env **)malloc(sizeof(t_env *));
	if (env_list == NULL)
		return (NULL);
	*env_list = NULL;
	while (env[i] != NULL)
	{
		split = ft_split(env[i], '=');
		if (split == NULL)
			return (env_error("ft_split"));
		ft_lstadd_back_ms(env_list, ft_lstnew_ms(split[0], split[1]));
		free(split);
		i++;
	}
	return (env_list);
}
/*
t_env	**init_env_copy(char **env)
{
	t_env	**env_list;
	t_env	*env_var;
	char	**split;

	env_list = NULL;
	while (*env)
	{
		env_var = (t_env *)malloc(sizeof(t_env));
		if (env_var == NULL)
			return (env_error("malloc"));
		split = ft_split(*env, '=');
		if (split == NULL)
			return (env_error("ft_split"));
		env_var->key = ft_strdup(split[0]);
		if (env_var->key == NULL)
			return (env_error("ft_strdup"));
		env_var->value = ft_strdup(split[1]);
		if (env_var->value == NULL)
			return (env_error("ft_strdup"));
		free(split);
		ft_lstadd_back_ms(env_list, ft_lstnew_ms(env_var->key, env_var->value));
		env++;
	}
	return (env_list);
}
*/
