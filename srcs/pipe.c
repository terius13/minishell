/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:51:16 by ting              #+#    #+#             */
/*   Updated: 2024/06/29 15:06:16 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	**init_pipe_ends(int num_cmds)
{
	int	**pipe_ends;
	int	i;

	i = 0;
	pipe_ends = (int **)malloc(sizeof(int *) * (num_cmds - 1));
	if (!pipe_ends)
		return (perror("malloc error"), NULL);
	while (i < num_cmds - 1)
	{
		pipe_ends[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_ends[i])
			return (perror("malloc error"), NULL);
		i++;
	}
	return (pipe_ends);
}

void	init_pipes(int **pipe_ends, int num_cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(pipe_ends[i]) == -1)
		{
			perror("pipe error");
			j = 0;
			while (j < num_cmds - 1)
			{
				free(pipe_ends[j]);
				j++;
			}
			free(pipe_ends);
			return ;
		}
		i++;
	}
}

void	free_pipe_ends(int **pipe_ends, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		free(pipe_ends[i]);
		i++;
	}
	free(pipe_ends);
}

void	close_pipe_ends(int **pipe_ends, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		close(pipe_ends[i][0]);
		close(pipe_ends[i][1]);
		i++;
	}
}
