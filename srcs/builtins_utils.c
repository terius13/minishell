/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:39:14 by asyed             #+#    #+#             */
/*   Updated: 2024/06/05 16:21:06 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"



char	*find_env(t_env **env_list, char *to_find)

{
	t_env	*current;
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

// handle more than 1 args
// find home path

void	builtin_cd(char **args)
{
	if (args[1] == NULL)
		return ;
	else
	{
		if (chdir(args[1]) != 0)
		{
			printf(C "shell@st42:$ " RST);
			printf("cd: '%s': No such file or directory\n", args[1]);
		}

	}
}

void	builtin_pwd(void)

{
	char	cwd[4086];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}

void	builtin_echo(char **args)

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

// see notes
// handle wrong args


void	builtin_exit(char **args, char *input, t_env **env)

{
	free_all(args, input, env);
	printf("exit\n");
	exit (0);
}
