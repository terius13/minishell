/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:22:50 by ting              #+#    #+#             */
/*   Updated: 2024/06/05 16:12:02 by ting             ###   ########.fr       */
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

	printf("In print parse\n");
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

void	check_builtins(t_cmd **cmds)
{
	t_cmd	*current;

	current = *cmds;
	while (current)
	{
		if (!ft_strcmp(current->cmd_arr[0], "echo") || !ft_strcmp(current->cmd_arr[0], "cd")
				|| !ft_strcmp(current->cmd_arr[0], "pwd") || !ft_strcmp(current->cmd_arr[0], "export")
				|| !ft_strcmp(current->cmd_arr[0], "unset") || !ft_strcmp(current->cmd_arr[0], "env")
				|| !ft_strcmp(current->cmd_arr[0], "exit"))
		{
			current->builtin = 1;
		}
		current = current->next;
	}
}


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

void parsing(t_lexer **lexer, t_cmd **cmds)
{
    int		i;
    int		arg_count;
    t_lexer	*curr_l;
    t_lexer	*temp_l;
    char	**arr;
    t_cmd   *cmd;

    curr_l = *lexer;
    while (curr_l)
    {
        arg_count = 0;
        temp_l = curr_l;
        while (temp_l && temp_l->type != 2)
        {
            arg_count++;
            temp_l = temp_l->next;
        }
        arr = ft_calloc(arg_count + 1, sizeof(char *));
        i = 0;
        cmd = new_cmd(arr);
        while (curr_l && curr_l->type != 2)
        {
            if (curr_l->type == 3)
            {
                if (curr_l->next && curr_l->next->type != 2 && curr_l->next->type != 4 && curr_l->next->type != 5 && curr_l->next->type != 6)
                {
                    curr_l = curr_l->next;
                    cmd->infile = ft_strdup(curr_l->str);
                }
                else
                    perror("no in/outfile"); //change to error handling later,if NULL return error
            }
            else if (curr_l->type == 4)
            {
                if (curr_l->next && curr_l->next->type != 2 && curr_l->next->type != 3 && curr_l->next->type != 5 && curr_l->next->type != 6)
                {
                    curr_l = curr_l->next;
                    cmd->outfile = ft_strdup(curr_l->str);
                }
                else
                    perror("no in/outfile"); //change to error handling later,if NULL return error
            }
			else if (curr_l->type == 5)
			{
				if (curr_l->next && curr_l->next->type != 2 && curr_l->next->type != 3 && curr_l->next->type != 4 && curr_l->next->type != 6)
                {
                    curr_l = curr_l->next;
                    cmd->hdoc_delimeter = ft_strdup(curr_l->str);
                }
                else
                    perror("no in/outfile"); //change to error handling later,if NULL return error
			}
			else if (curr_l->type == 6)
			{
				if (curr_l->next && curr_l->next->type != 2 && curr_l->next->type != 3 && curr_l->next->type != 5 && curr_l->next->type != 6)
                {
                    curr_l = curr_l->next;
                    cmd->outfile = ft_strdup(curr_l->str);
					cmd->append_re = 1;
                }
                else
                    perror("no in/outfile"); //change to error handling later,if NULL return error
			}
            else
            {
                arr[i] = ft_strdup(curr_l->str);
                i++;
            }
            curr_l = curr_l->next;
        }
        cmd_add_back(cmds, cmd);
        if (curr_l)
            curr_l = curr_l->next;
    }
	check_builtins(cmds);
}
