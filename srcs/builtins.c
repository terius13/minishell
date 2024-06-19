/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:35:19 by asyed             #+#    #+#             */
/*   Updated: 2024/06/14 11:43:46 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_builtins(t_cmd	**cmds, char **args, t_env **env_dup)

{
	if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args, env_dup);
	else if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		builtin_export(args, env_dup);
	else if (ft_strcmp(args[0], "unset") == 0)
		builtin_unset(args, env_dup);
	else if (ft_strcmp(args[0], "env") == 0)
		builtin_env(env_dup, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(cmds, env_dup, args);
	else
		printf("Command %s not found.\n", args[0]);
}

/*
int	main(int ac, char **av, char **env)

{
	char	*input;
	char	**args;
	t_env	**env_dup;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	
	env_dup = init_env_copy(env);
	if (env_dup == NULL)
	{
		perror ("init_env_copy");
		return (1);
	}
	while (1)
	{
		input = readline(C "shell@st42:$ " RST);
		if (input == NULL)
			break ; // exit if EOF or error, can be Ctrl + D
		args = ft_split(input, ' ');
		if (args == NULL)
		{
			perror("ft_split");
			free(input);
			break ;
		}
		execute_builtins(args, input, env_dup);
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		i = 0;
		free(args);
	}
	// free_all(args, input, env_dup);
	return (0);
}
*/