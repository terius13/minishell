/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:39:14 by asyed             #+#    #+#             */
/*   Updated: 2024/06/11 18:52:06 by asyed            ###   ########.fr       */
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

void	print_error(char *str)

{
	printf("shell@st42: %s\n", str);
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
			print_error("No such file or directory");
	}
	else if (ac > 2)
	{
		//printf(C "shell@st42:$ " RST);
		print_error("Too many arguments");
		
	}
	else
	{
		if (chdir(args[1]) != 0)
			print_error("No such file or directory");
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
