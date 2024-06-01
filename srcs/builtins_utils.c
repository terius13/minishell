/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:39:14 by asyed             #+#    #+#             */
/*   Updated: 2024/05/31 12:19:50 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void	builtin_cd(char **args)
{
	if (args[1] == NULL)
		return ;
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
}

void	builtin_pwd(void)

{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}

void	builtin_echo(char **args)
// might need to handle $ just in case
{
	int	i;

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
}

void	builtin_exit(char **args, char *input, t_env **env)

{
	free_all(args, input, env);
	printf("exit\n");
	exit (0);
}
