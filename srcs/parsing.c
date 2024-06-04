/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:22:50 by ting              #+#    #+#             */
/*   Updated: 2024/06/04 18:23:19 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//split on pipes
//then remove quotes
//store it in an array **cmd

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

	printf("In print parse\n");
	current = *cmds;
	while (current)
	{
		i = 0;
		while (current->cmd_arr[i])
		{
			printf("Pos[%d]:%s\n", i, current->cmd_arr[i]);
			i++;
		}
		current = current->next;
	}
}
/*
void	check_builtins(t_cmd **cmds)
{
	t_cmd	*current;

	current = *cmds;
	while (current)
	{
		if (current->cmd_arr[i])
		{

		}
	}
}
*/

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

void	parsing(t_lexer **lexer, t_cmd **cmds)
{
    int		i;
    int		arg_count;
    t_lexer	*curr_l;
    t_lexer	*temp_l;
    char	**arr;

    curr_l = *lexer;
    while (curr_l)
    {
        arg_count = 0;
        temp_l = curr_l;
		//count the number of str for arr
        while (temp_l && temp_l->type != 2)
        {
            arg_count++;
            temp_l = temp_l->next;
        }
        arr = ft_calloc(arg_count + 1, sizeof(char *));
        i = 0;
        while (curr_l && curr_l->type != 2)
        {
			if (curr_l->type == 3)
			{
				curr_l = curr_l->next;
				//check if next is not NULL
				//if NULL return error
				//assign curr_l->str to infile
			}
			else if (curr_l->type == 4)
			{
				curr_l = curr_l->next;
				//check if next is not NULL
				//if NULL return error
				//assign curr_l->str to outfile
			}
			else if (curr_l->type == 5)
			{
				curr_l = curr_l->next;
				//check if next is not NULL
				//if NULL return error
				//create a delimeter var in cmd struct
				//assign curr_l->str to delimeter
			}
			else if (curr_l->type == 6)
			{
				curr_l = curr_l->next;
				//check if next is not NULL
				//if NULL return error
				//assign curr_l->str to outfile
				//append_redirection, need to think how to tell if it is
			}
			else
			{
        	    arr[i] = ft_strdup(curr_l->str);
        	    i++;
			}
			curr_l = curr_l->next;
        }
        cmd_add_back(cmds, new_cmd(arr));
        if (curr_l)
            curr_l = curr_l->next;
    }
    printf("Entering print parse\n");
    print_parse(cmds);
}


