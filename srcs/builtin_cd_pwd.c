/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:26:40 by asyed             #+#    #+#             */
/*   Updated: 2024/06/19 18:36:22 by asyed            ###   ########.fr       */
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
	update_pwd(env_list);
	return (0);
}

void	update_pwd(t_env **env_list)

{
	char	cwd[4086];
	t_env	*current;

	current = *env_list;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("update pwd");
		return ;
	}
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(cwd);
			return ;
		}
		current = current->next;
	}	
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
