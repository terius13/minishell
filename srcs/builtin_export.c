/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:08:20 by asyed             #+#    #+#             */
/*   Updated: 2024/06/02 14:58:24 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_export(char **args, t_env **env_list)
{
	char	**split;
	char	*key;
	char	*value;
	t_env	*tmp;

	split = ft_split(args[1], '=');
	key = split[0];
	value = split[1];
	tmp = *env_list;
	if (key == NULL || value == NULL || ft_strchr(key, ' ')
		|| key[ft_strlen(key) + 1] != '=' || (value[0] -1) != '=')
	{
		printf("shell@st42: =%s not a valid identifier\n", value);
		free(split);
		return ;
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = value;
			free(split);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_ms(env_list, ft_lstnew_ms(key, value));
	free(split);
}
