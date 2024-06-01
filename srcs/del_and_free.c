/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:39:54 by asyed             #+#    #+#             */
/*   Updated: 2024/06/01 16:19:46 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_env_var(void *env_dup)

{
	t_env	*env_var;

	env_var = (t_env *)env_dup;
	//free(env_var->key);
	//free(env_var->value);
	free(env_var);
}

void	free_env(t_env	**env_list)
{
	t_env	*head;
	
	while (*env_list)
	{
		head = (**env_list).next;
		free((**env_list).key);
		free((**env_list).value);
		free(*env_list);
		*env_list = head;
	}
	*env_list = NULL;
}

void	free_all(char **args, char *input, t_env **env_dup)

{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	free(input);
	free_env(env_dup);
	free(env_dup);
}
