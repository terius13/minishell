/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:33:55 by ting              #+#    #+#             */
/*   Updated: 2024/06/09 16:32:16 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*new_cmd(char **arr)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd_arr = arr;
	new->in_pid = 0;  // set to std_int for now
	new->out_pid = 1; // set to std_out for now, change if open
	new->infile = NULL;
	new->outfile = NULL;
	new->builtin = 0;
	new->append_re = NULL;
	new->hdoc_delimeter = NULL;
	return (new);
}

void	cmd_add_back(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*current;

	if (!cmds || !new)
		return ;
	if (!*cmds)
	{
		*cmds = new;
		new->next = NULL;
	}
	else
	{
		current = *cmds;
		while (current->next)
			current = current->next;
		current->next = new;
		new->next = NULL;
	}
}
void	print_parse(t_cmd **cmds)
{
	t_cmd	*current;
	int		i;
	int		j;
	int		k;

	current = *cmds;
	j = 0;
	while (current)
	{
		i = 0;
		while (current->cmd_arr[i])
		{
			printf("Pos[%d]:%s\n", i, current->cmd_arr[i]);
			i++;
		}
		printf("Cmd[%d]:\n", j);
		printf("IN_PID: %d, OUT_PID: %d, INFILE: ", current->in_pid,
			current->out_pid);
		k = 0;
		if (current && current->infile)
		{
			while (current->infile[k])
			{
				printf("%s ", current->infile[k]);
				k++;
			}
		}
		printf(", OUTFILE: ");
		k = 0;
		if (current && current->outfile)
		{
			while (current->outfile[k])
			{
				printf("%s ", current->outfile[k]);
				k++;
			}
		}
		printf("\nBUILTINS: %d, HEREDOC: %s", current->builtin, current->hdoc_delimeter);
		printf(", APPENDRE: ");
		k = 0;
		if (current && current->append_re)
		{
			while (current->append_re[k])
			{
				printf("%s ", current->append_re[k]);
				k++;
			}
		}
		printf("\n");
		j++;
		current = current->next;
	}
}

int	cal_arg_count(t_lexer *curr_l)
{
	int	arg_count;

	arg_count = 0;
	while (curr_l && curr_l->type != 2)
	{
		arg_count++;
		curr_l = curr_l->next;
	}
	return (arg_count);
}

int	get_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

void	add_to_arr(char ***arr, char *str)
{
	int	size;

	size = get_arr_size(*arr);
	*arr = realloc(*arr, (size + 2) * sizeof(char *));
	(*arr)[size] = ft_strdup(str);
	(*arr)[size + 1] = NULL;
}

/*
void	remove_element(char **arr, int index, int arr_length)
{
	// Free the string at the specified index
	free(arr[index]);
	// Shift all elements after the index back by one
	while (index < arr_length - 1)
	{
		arr[index] = arr[index + 1];
		index++;
	}
	// Nullify the last element
	arr[arr_length - 1] = NULL;
}
*/
