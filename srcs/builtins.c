/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:35:19 by asyed             #+#    #+#             */
/*   Updated: 2024/05/28 18:58:42 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_builtins(char **args, char *input, char **env)

{
	if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args);

	else if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd();
	// export

	// unset

	else if (ft_strcmp(args[0], "env") == 0)
		builtin_env(env);
	else if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(args, input);
	else
		printf("Command %s not found.\n", args[0]);
}

void	builtin_cd(char **args)
{
	if (args[1] == NULL)
		return;
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
}

void	builtin_env(char **env)

{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
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

void	builtin_exit(char **args, char *input)

{
	free_all(args, input);
	printf("exit\n");
	exit (0);
}

void	free_all(char **args, char *input)

{
	free(args);
	free(input);
}

int		main(int ac, char **av, char **env)

{
	char	*input;
	char	**args;

	while (1)
	{
		input = readline(C "shell@st42:$ " RST);
		if (input == NULL)
			break; // exit if EOF or error, can be Ctrl + D

		// SPLIT HAS MEMORY ISSUE
		args = ft_split(input, ' ');
		if (args == NULL)
		{
			perror("ft_split");
			free(input);
			break;
		}
		execute_builtins(args, input, env);
		free_all(args, input);
	}
	return(0);
}
