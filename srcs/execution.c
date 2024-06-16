/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:10:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/16 16:10:31 by ting             ###   ########.fr       */
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
			return (print_error("dup2 infile"), 1);
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
		if ()
	}
}

void	handle_redirection(t_cmd *cmd, t_ms_state *stat)
{
	if (cmd->infile)
		handle_infile(cmd, stat);
	if (cmd->outfile)
		handle_outfile();
}
