/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_status_envdup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:23:09 by asyed             #+#    #+#             */
/*   Updated: 2024/07/05 15:36:23 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ms_state	*init_status(void)
{
	t_ms_state	*status;

	status = (t_ms_state *)malloc(sizeof(t_ms_state));
	if (status == NULL)
	{
		perror("status");
		exit(1);
	}
	status->exit_status = 0;
	return (status);
}

t_env	**init_envdup(t_ms_state *status, char **env)
{
	t_env	**env_dup;

	env_dup = init_env_copy(env);
	if (env_dup == NULL)
	{
		perror("init_env_copy");
		free(status);
		status = NULL;
		exit(1);
	}
	return (env_dup);
}
