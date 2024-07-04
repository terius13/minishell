/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:35:19 by asyed             #+#    #+#             */
/*   Updated: 2024/07/04 14:45:08 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_builtins(t_cmd **cmds, char **args, t_env **env_dup,
		t_ms_state *status)
{
	if (ft_strcmp(args[0], "echo") == 0)
		status->exit_status = builtin_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		status->exit_status = builtin_cd(args, env_dup);
	else if (ft_strcmp(args[0], "pwd") == 0)
		status->exit_status = builtin_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		status->exit_status = builtin_export(args, env_dup,
				status->exit_status);
	else if (ft_strcmp(args[0], "unset") == 0)
		status->exit_status = builtin_unset(args, env_dup);
	else if (ft_strcmp(args[0], "env") == 0)
		status->exit_status = builtin_env(env_dup, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		status->exit_status = builtin_exit(cmds, env_dup, args, status);
	else
		status->exit_status = 127;
}
