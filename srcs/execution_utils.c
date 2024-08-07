/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:04:57 by ting              #+#    #+#             */
/*   Updated: 2024/07/05 17:26:37 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmds_len(t_cmd *cmds)
{
	t_cmd	*current;
	int		num_cmds;

	num_cmds = 0;
	current = cmds;
	while (current)
	{
		num_cmds++;
		current = current->next;
	}
	return (num_cmds);
}

char	*join_key_value(const char *key, const char *value)
{
	int		len;
	char	*result;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	result = (char *)malloc(len * sizeof(char));
	if (result)
	{
		ft_strlcpy(result, key, len);
		ft_strlcat(result, "=", len);
		ft_strlcat(result, value, len);
	}
	return (result);
}

// Function to convert linked list to char ** array
char	**env_in_arr(t_env **env)
{
	int		size;
	char	**env_cpy;
	t_env	*current;
	int		i;

	i = 0;
	size = 0;
	current = *env;
	while (current)
	{
		size++;
		current = current->next;
	}
	env_cpy = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!env_cpy)
		return (NULL);
	current = *env;
	while (current)
	{
		env_cpy[i] = join_key_value(current->key, current->value);
		current = current->next;
		i++;
	}
	return (env_cpy);
}

char	*find_path(char *cmd, t_env **env)
{
	char	*path_in_env;
	char	**path_segments;
	char	*path;
	char	*cmd_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_in_env = find_env(env, "PATH");
	if (path_in_env == NULL)
		return (NULL);
	path_segments = ft_split(path_in_env, ':');
	i = 0;
	while (path_segments[i])
	{
		path = ft_strjoin(path_segments[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		if (access(cmd_path, X_OK) == 0)
			return (free_array(path_segments), free(path), cmd_path);
		free(path);
		free(cmd_path);
		i++;
	}
	return (free_array(path_segments), NULL);
}

int	illegal_builtins(t_cmd *current)
{
	if (current->builtin && (!ft_strcmp(current->cmd_arr[0], "cd")
			|| !ft_strcmp(current->cmd_arr[0], "export")
			|| !ft_strcmp(current->cmd_arr[0], "unset")
			|| !ft_strcmp(current->cmd_arr[0], "exit")))
	{
		return (1);
	}
	return (0);
}
