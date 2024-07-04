/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:31:41 by ting              #+#    #+#             */
/*   Updated: 2024/07/04 11:49:51 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmd		**cmds;
	t_env		**env_dup;
	t_ms_state	*status;

	(void)ac;
	(void)av;
	status = init_status();
	if (signal_handlers_setup(status) != 0)
		return (1);
	env_dup = init_envdup(status, env);
	cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	*cmds = NULL;
	minishell_loop(cmds, env_dup, status);
	return (0);
}
