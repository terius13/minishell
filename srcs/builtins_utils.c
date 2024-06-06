/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:39:14 by asyed             #+#    #+#             */
/*   Updated: 2024/06/06 11:54:04 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_env(t_env **env_list, char *to_find)

{
	t_env *current;

	current = *env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, to_find) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

void	print_error_cd(char *args)

{
	//printf(C "shell@st42:$ " RST);
	printf("bash: cd: '%s': No such file or directory\n", args);
}

void	builtin_cd(char **args, t_env **env_list)
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
			print_error_cd(home);
	}
	else if (ac > 2) // why not handling more than 1 args properly?
	{
		//printf(C "shell@st42:$ " RST);
		printf("bash: cd: too many arguments\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
			print_error_cd(args[1]);
	}
}

void	builtin_pwd(void)

{
	char cwd[4086];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}

void	builtin_echo(char **args)

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
}


void	builtin_exit(char **args, char *input, t_env **env)

{
	int	exit_stats;
	int	ac;
	int	i;
	int	av;

	exit_stats = 0;
	ac = 0;
	i = 0;
	
	while (args[ac])
		ac++;
	printf("exit\n");
	if (ac > 2 && args[1] != NULL && ft_isdigit(args[1][i]))
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	if (args[1] != NULL)
	{
		while (args[1][i])
		{
			if (ft_isdigit(args[1][i]) == 0 || (args[1][i] != '-' && ft_isdigit(args[1][i + 1]) == 0))
			{
				printf("bash: exit: %s: numeric arguments required\n", args[1]);
				exit_stats = 2;
				break;
			}
			i++;
		}
		if (exit_stats == 0)
		{
			av = ft_atoi(args[1]);
			exit_stats = av & 0xFF; // process only lower 8 bits
		}
	}
	free_all(args, input, env);
	exit(exit_stats);
}
