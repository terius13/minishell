/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:04:57 by ting              #+#    #+#             */
/*   Updated: 2024/06/20 15:51:10 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
