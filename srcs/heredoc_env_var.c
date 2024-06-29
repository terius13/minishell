/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:57:09 by ting              #+#    #+#             */
/*   Updated: 2024/06/29 14:59:31 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*replace_env_var_heredoc(char **line, t_env **env, t_ms_state *stat,
		char *result)
{
	char	*var_name;
	char	*var_value;
	char	*end;
	int		free_flag;
	char	*temp_result;

	free_flag = 0;
	end = *line + 1;
	if (*end == '?')
		end++;
	else
		while (ft_isalnum(*end) || *end == '_')
			end++;
	var_name = ft_substr(*line + 1, 0, end - (*line + 1));
	var_value = get_env_value(var_name, &free_flag, env, stat);
	if (var_value)
		temp_result = ft_strjoin(result, var_value);
	else
		temp_result = ft_strjoin(result, "");
	free(result);
	result = temp_result;
	*line = end;
	if (free_flag)
		free(var_value);
	return (result);
}

char	*env_var_heredoc(char *line, t_env **env, t_ms_state *stat)
{
	char	*result;
	char	*normal_char;
	char	*temp_result;

	result = ft_strdup("");
	while (*line)
	{
		if (*line == '$' && (ft_isalnum(*(line + 1)) || *(line + 1) == '?'))
			result = replace_env_var_heredoc(&line, env, stat, result);
		else
		{
			normal_char = ft_substr(line, 0, 1);
			temp_result = ft_strjoin(result, normal_char);
			free(result);
			free(normal_char);
			result = temp_result;
			line++;
		}
	}
	return (result);
}
