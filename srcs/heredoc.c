/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:00:15 by ting              #+#    #+#             */
/*   Updated: 2024/07/05 15:34:07 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*trim_whitespace(char *str)
{
	char	*end;

	while (*str == ' ' || *str == '\n' || *str == '\r')
		str++;
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\n' || *end == '\r'))
		end--;
	*(end + 1) = '\0';
	return (str);
}

int	write_to_heredoc_file(t_cmd *current, char *expanded_line, int fd)
{
	char	*trimmed_line;

	if (expanded_line[0] != '\0' && ft_strlen(expanded_line) > 1)
		trimmed_line = trim_whitespace(expanded_line);
	else
	{
		trimmed_line = ft_strdup("");
		free(expanded_line);
	}
	if (ft_strcmp(trimmed_line, current->hdoc_delimeter) == 0)
	{
		free(trimmed_line);
		return (1);
	}
	ft_putendl_fd(trimmed_line, fd);
	free(trimmed_line);
	return (0);
}

void	heredoc_loop(t_cmd *current, t_env **env, t_ms_state *stat, int fd)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (g_reset_cancel == 2)
		{
			free(line);
			return ;
		}
		if (!line)
		{
			printf("\nshell@st42:$ warning: %s (wanted `%s')\n",
				"here-document delimited by end-of-file",
				current->hdoc_delimeter);
			break ;
		}
		expanded_line = env_var_heredoc(line, env, stat);
		free(line);
		if (write_to_heredoc_file(current, expanded_line, fd))
			break ;
	}
}

void	here_doc(t_cmd *current, t_env **env, t_ms_state *stat)
{
	int					fd;
	struct sigaction	old_sa;
	struct sigaction	old_ign;
	int					i;

	i = 0;
	if (!current->hdoc_delimeter)
		return ;
	save_original_signal(&old_sa, &old_ign);
	here_doc_set_up();
	while (current->infile[i])
	{
		if (ft_strcmp(current->infile[i], ".hdc.tmp") == 0)
			break ;
		i++;
	}
	fd = open(current->infile[i], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
		return (perror("open"));
	here_doc_set_up();
	heredoc_loop(current, env, stat, fd);
	restore_original_signal(&old_sa, &old_ign);
	close(fd);
}
