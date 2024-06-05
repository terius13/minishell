/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:15:09 by asyed             #+#    #+#             */
/*   Updated: 2024/06/05 16:03:49 by asyed            ###   ########.fr       */
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
		ft_lstadd_back_ms(env_list, ft_lstnew_ms(ft_strdup(split[0]), ft_strdup(split[1])));
		free_split(split);
		i++;
	}
	return (env_list);
}
