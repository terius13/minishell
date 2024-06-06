/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:05:41 by asyed             #+#    #+#             */
/*   Updated: 2024/06/06 16:57:07 by asyed            ###   ########.fr       */
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

void	not_numeric(char **args, char *input, t_env **env)

{
	int	exit_stats;

	exit_stats = 2;
	printf("bash: exit: %s: numeric arguments required\n", args[1]);
	free_all(args, input, env);
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

	av = ft_atoi(args[1]);
	exit_stats = av & 0xFF; // process only lower 8 bits
	return (exit_stats);
}
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
				not_numeric(args, input, env);
			i++;
		}
	}
	if (too_many_args(args))
		return ;
	if (exit_stats == 0)
		exit_stats = confirmed_exit_status(args);
	free_all(args, input, env);
	exit(exit_stats);
}
