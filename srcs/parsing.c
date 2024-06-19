/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:22:50 by ting              #+#    #+#             */
/*   Updated: 2024/06/14 16:48:39 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_builtins(t_cmd **cmds)
{
	t_cmd	*current;

	current = *cmds;
	while (current)
	{
		if (current->cmd_arr && current->cmd_arr[0]
			&& (!ft_strcmp(current->cmd_arr[0], "echo")
				|| !ft_strcmp(current->cmd_arr[0], "cd")
				|| !ft_strcmp(current->cmd_arr[0], "pwd")
				|| !ft_strcmp(current->cmd_arr[0], "export")
				|| !ft_strcmp(current->cmd_arr[0], "unset")
				|| !ft_strcmp(current->cmd_arr[0], "env")
				|| !ft_strcmp(current->cmd_arr[0], "exit")))
		{
			current->builtin = 1;
		}
		current = current->next;
	}
}

int	handle_redirection(t_lexer **curr_l, t_cmd *cmd)
{
	if ((*curr_l)->type == 3)
	{
		if ((*curr_l)->next && (*curr_l)->next->type == 1)
		{
			*curr_l = (*curr_l)->next;
			add_to_arr(&cmd->infile, (*curr_l)->str);
		}
		else
			return (print_error("syntax error"), 1);
	}
	else if ((*curr_l)->type == 4)
	{
		if ((*curr_l)->next && (*curr_l)->next->type == 1)
		{
			*curr_l = (*curr_l)->next;
			add_to_arr(&cmd->outfile, (*curr_l)->str);
		}
		else
			return (print_error("syntax error"), 1);
	}
	return (0);
}

int	handle_append_or_heredoc(t_lexer **curr_l, t_cmd *cmd)
{
	if ((*curr_l)->type == 5)
	{
		if ((*curr_l)->next && (*curr_l)->next->type == 1)
		{
			*curr_l = (*curr_l)->next;
			cmd->hdoc_delimeter = ft_strdup((*curr_l)->str);
		}
		else
			return (print_error("syntax error"), 1);
	}
	else if ((*curr_l)->type == 6)
	{
		if ((*curr_l)->next && (*curr_l)->next->type == 1)
		{
			*curr_l = (*curr_l)->next;
			add_to_arr(&cmd->outfile, (*curr_l)->str);
			add_to_arr(&cmd->append_re, (*curr_l)->str);
		}
		else
			return (print_error("syntax error"), 1);
	}
	return (0);
}


int handle_lexer(t_lexer **curr_l, t_cmd **cmd, char **arr)
{
    int i;

	i = 0;
    while (*curr_l && (*curr_l)->type != 2)
    {
        if ((*curr_l)->type == 3 || (*curr_l)->type == 4)
        {
            if (handle_redirection(curr_l, *cmd))
                return (free_array(arr), free(*cmd), 1);
        }
        else if ((*curr_l)->type == 5 || (*curr_l)->type == 6)
        {
            if (handle_append_or_heredoc(curr_l, *cmd))
                return (free_array(arr), free(*cmd), 1);
        }
        else
            arr[i++] = ft_strdup((*curr_l)->str);
        *curr_l = (*curr_l)->next;
    }
    return (0);
}

int parsing(t_lexer **lexer, t_cmd **cmds)
{
    int     arg_count;
    t_lexer *curr_l;
    char    **arr;
    t_cmd   *cmd;

    curr_l = *lexer;
    while (curr_l)
    {
        arg_count = cal_arg_count(curr_l);
        arr = ft_calloc(arg_count + 1, sizeof(char *));
        cmd = new_cmd(arr);
        if (handle_lexer(&curr_l, &cmd, arr))
            return (1);
        cmd_add_back(cmds, cmd);
        if (curr_l)
            curr_l = curr_l->next;
    }
    return (0);
}

