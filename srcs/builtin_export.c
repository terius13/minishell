/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:08:20 by asyed             #+#    #+#             */
/*   Updated: 2024/06/04 11:46:38 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_current_export(t_env *tmp, char *key, char *value)
{
	free(tmp->value);
	tmp->value = value;
	free(key);
}

int	export_error_check(char *args)

{
	int	i;

	if (args == NULL || args[0] == '\0')
		return (-1);
	if (args[0] == '=' || ((isalpha(args[0]) == 0) && args[0] != '_'))
	{
		printf("shell@st42: export: '%s': not a valid identifier\n", args);
		return (-1);
	}
	i = 1;
	while (args[i])
	{
		if (args[i] == '=')
			return (i + 1) ;
		if ((isalnum(args[i]) == 0) && args[i] != '_')
		{
			printf("shell@st42: export: '%s': not a valid identifier\n", args);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	assign_key_value(char **args, int equal, char **key, char **value)
{
	if (equal == 0)
	{
		*key = ft_strdup(args[1]);
		*value = NULL;
	}
	else
	{
		*key = ft_strndup(args[1], equal - 1);
		*value = ft_strdup(&args[1][equal]);
	}
}
void	builtin_export(char **args, t_env **env_list)
{
	char	*key;
	char	*value;
	t_env	*tmp;
	int		equal;

	equal = export_error_check(args[1]);
	if (equal == -1)
		return ;
	assign_key_value(args, equal, &key, &value);
	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			update_current_export(tmp, key, value);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_ms(env_list, ft_lstnew_ms(key, value));
}


