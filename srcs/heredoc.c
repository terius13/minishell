/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:00:15 by ting              #+#    #+#             */
/*   Updated: 2024/06/28 19:06:33 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*trim_whitespace(char *str)
{
	char	*end;

	// Trim leading space
	while (*str == ' ' || *str == '\n' || *str == '\r')
		str++;

	if (*str == 0)
		return (str);

	// Trim trailing space
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\n' || *end == '\r'))
		end--;

	// Write new null terminator
	*(end + 1) = '\0';
	return (str);
}

char *env_var_heredoc(char *line, t_env **env, t_ms_state *stat)
{
    char *result;
    char *end;
    char *var_name;
    char *var_value;
    char *normal_char;
    char *temp_result;
	int		free_flag;

    result = ft_strdup("");
	free_flag = 0;
    while (*line)
    {
        if (*line == '$' && (ft_isalnum(*(line + 1)) || *(line + 1) == '?'))
        {
            end = line + 1;
			if (*end == '?')
                end++;
            else
                while (ft_isalnum(*end) || *end == '_')
                    end++;
            var_name = ft_substr(line + 1, 0, end - line - 1);
			printf("Variable name: %s\n", var_name); 
			var_value = get_env_value(var_name, &free_flag, env, stat);
            printf("Variable value: %s\n", var_value);  
            if (var_value)
                temp_result = ft_strjoin(result, var_value);
            else
                temp_result = ft_strjoin(result, "");
            free(result);
            result = temp_result;
            line = end;  // Move line pointer past the variable name
			if (free_flag)
				free(var_value);
        }
        else
        {
            normal_char = ft_substr(line, 0, 1);
            temp_result = ft_strjoin(result, normal_char);
            free(result);  // Free previous result
            free(normal_char);  // Free normal_char after use
            result = temp_result;
            line++;  // Move to the next character in the input line
        }
    }
    return (result);
}

void    here_doc(t_cmd *current, t_env **env, t_ms_state *stat)
{
    char    *line;
    int     fd;
    char    *file;
    struct sigaction old_sa;
    char    *trimmed_line;
    char    *expanded_line;

    if (!current->hdoc_delimeter)
        return;
    file = "./heredoc.tmp";
    fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
    if (here_doc_set_up(&old_sa) != 0)
        return;
    while (1)
    {
        if (g_reset_cancel == 2)
            break;
        write(1, "> ", 2);
        line = get_next_line(0);  // 0 is the file descriptor for standard input
        if (g_reset_cancel == 2)
        {
            free (line);
            break;
        }
        if (!line)
        {
            printf("shell@st42:$ warning: here-document delimited by end-of-file (wanted `%s')\n", current->hdoc_delimeter);
            break;
        }
        expanded_line = env_var_heredoc(line, env, stat);
        if (expanded_line[0] != '\0' && ft_strlen(expanded_line) > 1)
            trimmed_line = trim_whitespace(expanded_line);
        else
        {
            trimmed_line = ft_strdup("");
            free(expanded_line);
        }
        if (ft_strcmp(trimmed_line, current->hdoc_delimeter) == 0)
        {
            free(line);
            free(trimmed_line);
            trimmed_line = NULL;
            break;
        }
        ft_putendl_fd(trimmed_line, fd);
        free(trimmed_line);
        free(line);
    }
    if (sigaction(SIGINT, &old_sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    close(fd);
    if (!current->infile)
        current->infile = ft_calloc(2, sizeof(char *));
    add_to_arr(&(current->infile), file);
}