/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:33:55 by ting              #+#    #+#             */
/*   Updated: 2024/06/06 15:37:02 by ting             ###   ########.fr       */
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
	new->in_pid = 0;  //set to std_int for now
	new->out_pid = 1; //set to std_out for now, change if open
	new->infile = NULL;
	new->outfile = NULL;
	new->builtin = 0;
	new->append_re = 0;
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
		printf("IN_PID: %d, OUT_PID: %d, INFILE: %s, OUTFILE: %s\n", current->in_pid, current->out_pid, current->infile, current->outfile);
		printf("BUILTINS: %d, APPENDRE: %d, HEREDOC: %s\n", current->builtin, current->append_re, current->hdoc_delimeter);
		j++;
		current = current->next;
	}
}

int    cal_arg_count(t_lexer *curr_l)
{
    int     arg_count;
    
    arg_count = 0;
    while (curr_l && curr_l->type != 2)
    {
        arg_count++;
        curr_l = curr_l->next;
    }
    return (arg_count);
}

/*
void remove_element(char **arr, int index, int arr_length)
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