/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:39:54 by asyed             #+#    #+#             */
/*   Updated: 2024/06/05 10:39:23 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
void	free_env(t_env	**env_list)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env_list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	free(env_list);
	//*env_list = NULL;
}

void	free_all(char **args, char *input, t_env **env_dup)

{
	free_split(args);
	// free(args);
	free(input);
	free_env(env_dup);
	// free(env_dup);
}
