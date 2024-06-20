/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:04:57 by ting              #+#    #+#             */
/*   Updated: 2024/06/20 20:29:51 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *join_key_value(const char *key, const char *value)
{
    int len;
	char *result;
	
	len = strlen(key) + strlen(value) + 2; // +2 for '=' and '\0'
    result = (char *)malloc(len * sizeof(char));
    if (result)
    {
        ft_strlcpy(result, key, len);
        ft_strlcat(result, "=", len);
        ft_strlcat(result, value, len);
    }
    return result;
}

// Function to convert linked list to char ** array
char **env_in_arr(t_env **env)
{
	int 	size;
	char **env_cpy;
	t_env *current;
	int 	i;

	i = 0;
	size = 0;
	current = *env;
	while (current)
    {
        size++;
        current = current->next;
    }
    env_cpy = (char **)calloc(size + 1, sizeof(char *));
    if (!env_cpy)
        return NULL;
    current = *env;
    while (current)
    {
        env_cpy[i] = join_key_value(current->key, current->value);
        current = current->next;
        i++;
    }
    return (env_cpy);
}

char    *find_path(char *cmd, t_env **env)
{
    char    *path_in_env;
    char    **path_segments;
    char    *path;
    char    *cmd_path;
    int     i;
    
    path_in_env = find_env(env, "PATH");
    path_segments = ft_split(path_in_env, ':');
    i = 0;
    while(path_segments[i])
    {
        path = ft_strjoin(path_segments[i], "/");
        cmd_path = ft_strjoin(path, cmd);
        if (access(cmd_path, X_OK) != 0)
        {
            free(path);
            free(cmd_path);
        }
        else
            return (free_array(path_segments), free(path), cmd_path);
        i++;
    }
    return (free_array(path_segments), NULL);
}
