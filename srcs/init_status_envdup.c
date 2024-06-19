/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_status_envdup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:23:09 by asyed             #+#    #+#             */
/*   Updated: 2024/06/19 18:23:38 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ms_state	*init_status()

{
	t_ms_state	*status;

	status = (t_ms_state *)malloc(sizeof(t_ms_state));
	if (status == NULL)
	{
		perror ("status");
		return (NULL);
	}
	status->exit_status = 0;
	return (status);
}

t_env	**init_status_and_envdup(t_ms_state **status, char **env)

{
	t_env	**env_dup;

	*status = init_status();
	if (status == NULL)
		return (NULL);
	env_dup = init_env_copy(env);
	if (env_dup == NULL)
	{
		perror("init_env_copy");
		free(*status);
		*status = NULL;
		return(NULL);
	}
	return (env_dup);
}