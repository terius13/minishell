/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:05:41 by asyed             #+#    #+#             */
/*   Updated: 2024/06/11 15:15:05 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_negative(char **args)
{
	int	i;

	i = 0;
	if (args[1][0] == '-' && args[1][i + 1])
		i = 1;
	return (i);
}

// NEED TO FREE ALL
/*

void	not_numeric(char **args, char *input, t_env **env)

{
	int	exit_stats;

	exit_stats = 2;
	printf("bash: exit: %s: numeric arguments required\n", args[1]);
	// free_all(args, input, env);
	exit(exit_stats);
}

*/
void	not_numeric(char **args)

{
	int	exit_stats;

	exit_stats = 2;
	printf("bash: exit: %s: numeric arguments required\n", args[1]);
	// free_all(args, input, env);
	exit(exit_stats);
}

int	too_many_args(char **args)
{
	int ac;

	ac = 0;
	while (args[ac])
		ac++;
	if (ac > 2)
	{
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	confirmed_exit_status(char **args)
{
	int	av;
	int exit_stats;

	if (args[1] != NULL)
	{
		av = ft_atoi(args[1]);
		exit_stats = av & 0xFF; // process only lower 8 bits
	}
	else
	{
		exit_stats = 0;
	}
	return (exit_stats);
}
/*

// NEED TO FREE ARGS AND INPUT

void	builtin_exit(char **args, char *input, t_env **env)

{
	int	exit_stats;
	int	i;

	exit_stats = 0;
	i = 0;
	printf("exit\n");
	if (args[1] != NULL)
	{
		i = check_negative(args);
		while (args[1][i])
		{
			if (ft_isdigit(args[1][i]) == 0)
				not_numeric(args); // ADD ARGS AND INPUT TO FREE
			i++;
		}
	}
	if (too_many_args(args))
		return ;
	if (exit_stats == 0)
		exit_stats = confirmed_exit_status(args);
	//free_bi(args, input, env);
	free_env(env);
	exit(exit_stats);
}
*/

void	builtin_exit(t_cmd	**cmds, t_env	**env, char **args)

{
	int	exit_stats;
	int	i;

	exit_stats = 0;
	i = 0;
	printf("exit\n");
	if (args[1] != NULL)
	{
		i = check_negative(args);
		while (args[1][i])
		{
			if (ft_isdigit(args[1][i]) == 0)
				not_numeric(args); // ADD ARGS AND INPUT TO FREE
			i++;
		}
	}
	if (too_many_args(args))
		return ;
	if (exit_stats == 0)
		exit_stats = confirmed_exit_status(args);
	//free_bi(args, input, env); //change function to take in t_cmd, so able to use freeall_and_exit to free everything
	free_all_and_exit(cmds, env);
	exit(exit_stats);
}
