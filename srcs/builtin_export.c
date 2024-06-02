/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:08:20 by asyed             #+#    #+#             */
/*   Updated: 2024/06/02 21:00:25 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_current_export(t_env *tmp, char *value, char **split)
{
	free(tmp->value);
	tmp->value = ft_strdup(value);
	free_split(split);
}
char	*assign_split1(char **split)
{
	if (split[1])
		return (split[1]);
	else
		return ("");
}
void	builtin_export(char **args, t_env **env_list)
{
	char	**split;
	char	*key;
	char	*value;
	t_env	*tmp;

	split = ft_split(args[1], '=');
	tmp = *env_list;

	// UPDATE CONDITION, CHECK FOR ARGS, NOT NULL, NOT = AND BEFORE = IS ALNUM OR _
	
	if (args[1] == NULL || args[1][0] == '\0' || ft_strchr(args[1], '=') ==  args[1]) // can only check after parsing
	{
		printf("shell@st42: export: '%s': not a valid identifier\n", args[1]);
		free_split(split);
		return ;
	}
	key = split[0];
	value = ft_strdup(assign_split1(split));
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free_current_export(tmp, value, split);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_ms(env_list, ft_lstnew_ms(key, value));
	free (split);
}


