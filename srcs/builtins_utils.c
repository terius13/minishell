/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:39:14 by asyed             #+#    #+#             */
/*   Updated: 2024/06/15 17:28:56 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_cd(char **args, t_env **env_list)
{
	int		ac;
	char	*home;

	ac = 0;
	while (args[ac])
		ac++;
	if (args[1] == NULL)
	{
		home = find_env(env_list, "HOME");
		if (chdir(home) != 0)
		{
			print_error("No such file or directory");
			return (1);
		}
	}
	else if (ac > 2)
	{
		//printf(C "shell@st42:$ " RST);
		print_error("Too many arguments");
		return (1);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			print_error("No such file or directory");
			return (1);
		}
	}
	return (0);
}

int	builtin_pwd(void)

{
	char cwd[4086];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);	
}

int		builtin_echo(char **args, int exit_status)

{
	int i;

	i = 1;
	if (args[i] != NULL && (ft_strcmp(args[i], "-n") == 0))
	{
		i++;
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	}
	else
	{
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	return (exit_status);
}
