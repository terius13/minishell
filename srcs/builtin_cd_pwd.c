/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:26:40 by asyed             #+#    #+#             */
/*   Updated: 2024/07/04 11:59:26 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_old(t_env **env_list)
{
	t_env	*current;
	char	*old_pwd;

	current = *env_list;
	old_pwd = find_env(env_list, "PWD");
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			if (current->value != NULL)
			{
				free(current->value);
				current->value = NULL;
			}
			current->value = ft_strdup(old_pwd);
			return ;
		}
		current = current->next;
	}
	ft_add_env_back_node(env_list, ft_new_env_node(ft_strdup("OLDPWD"),
			ft_strdup(old_pwd)));
}

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
			return (print_error("No such file or directory"), 1);
	}
	else if (ac > 2)
		return (print_error("Too many arguments"), 1);
	else
	{
		if (chdir(args[1]) != 0)
			return (print_error("No such file or directory"), 1);
	}
	update_old(env_list);
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
			if (current->value != NULL)
			{
				free(current->value);
				current->value = NULL;
			}
			current->value = ft_strdup(cwd);
			return ;
		}
		current = current->next;
	}
}

int	builtin_pwd(void)
{
	char	cwd[4086];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}
