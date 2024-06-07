/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:39:54 by asyed             #+#    #+#             */
/*   Updated: 2024/06/07 11:30:52 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}
void	free_env(t_env	**env_list)
{
	t_env	*tmp;
	t_env	*next;

	if (env_list == NULL || *env_list == NULL)
		return ;
	tmp = *env_list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key)
		{
			free(tmp->key);
			tmp->key = NULL;
		}
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		free(tmp);
		tmp = next;
	}
	*env_list = NULL;
	//free(env_list);
}

void	free_all(char **args, char *input, t_env **env_dup)

{
	free_split(args);
	if (input)
	{
		free(input);
		input = NULL;
	}
	free_env(env_dup);
}
