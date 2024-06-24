/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:46:24 by ting              #+#    #+#             */
/*   Updated: 2024/06/24 17:38:26 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// check to see if the file is append_re
int	is_append_re(char *filename, char **append_re)
{
	int	i;

	i = 0;
	while (append_re && append_re[i])
	{
		if (ft_strcmp(filename, append_re[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	handle_infile(t_cmd *cmd, t_ms_state *stat)
{
	int	i;
	int	fd;
	int	last_fd;

	i = 0;
	last_fd = -1;
	while (cmd->infile[i])
	{
		fd = open(cmd->infile[i], O_RDONLY);
		if (fd == -1)
			return (stat->exit_status = 1,
				print_error("No such file or directory"), 1);
		if (last_fd != -1)
			close(last_fd);
		last_fd = fd;
		i++;
	}
	if (last_fd != -1)
	{
		if (dup2(last_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 infile");
			return (print_error("dup2 infile"), 1);
		}
		close(last_fd);
	}
	return (0);
}

int	handle_outfile(t_cmd *cmd, t_ms_state *stat)
{
	int	i;
	int	fd;
	int	last_fd;

	i = 0;
	last_fd = -1;
	while (cmd->outfile[i])
	{
		if (is_append_re(cmd->outfile[i], cmd->append_re))
		{
			fd = open(cmd->outfile[i], O_RDWR | O_CREAT | O_APPEND, 0777);
		}
		else
		{
			fd = open(cmd->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		}
		if (fd == -1)
			return (stat->exit_status = 1,
				print_error("No such file or directory"), 1);
		if (last_fd != -1)
			close(last_fd);
		last_fd = fd;
		i++;
	}
	if (last_fd != -1)
	{
		if (dup2(last_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 outfile");
			return (print_error("dup2 outfile"), 1);
		}
		close(last_fd);
	}
	return (0);
}

int	do_redirection(t_cmd *cmd, t_ms_state *stat)
{
	if (cmd->infile)
	{
		if (handle_infile(cmd, stat))
			return (1);
	}
	if (cmd->outfile)
	{
		if (handle_outfile(cmd, stat))
			return (1);
	}
	return (0);
}