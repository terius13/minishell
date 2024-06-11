/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:22:50 by ting              #+#    #+#             */
/*   Updated: 2024/06/11 14:57:43 by asyed            ###   ########.fr       */
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
				&& (!ft_strcmp(current->cmd_arr[0], "echo") || !ft_strcmp(current->cmd_arr[0], "cd")
				|| !ft_strcmp(current->cmd_arr[0], "pwd") || !ft_strcmp(current->cmd_arr[0], "export")
				|| !ft_strcmp(current->cmd_arr[0], "unset") || !ft_strcmp(current->cmd_arr[0], "env")
				|| !ft_strcmp(current->cmd_arr[0], "exit")))
		{
			current->builtin = 1;
		}
		current = current->next;
	}
}

void handle_redirection(t_lexer **curr_l, t_cmd *cmd)
{
	if (!curr_l || !*curr_l || !cmd)
    {
        perror("Null pointer");
        return;
    }
    if ((*curr_l)->type == 3)
    {
        if ((*curr_l)->next && (*curr_l)->next->type == 1)
        {
            *curr_l = (*curr_l)->next;
            add_to_arr(&cmd->infile, (*curr_l)->str);
		}
        else
            perror("no infile"); //need to change to error handling later
    }
    else if ((*curr_l)->type == 4)
    {
        if ((*curr_l)->next && (*curr_l)->next->type == 1)
        {
            *curr_l = (*curr_l)->next;
            add_to_arr(&cmd->outfile, (*curr_l)->str);
        }
        else
            perror("no outfile"); //need to change to error handling later
    }
}

void handle_append(t_lexer **curr_l, t_cmd *cmd)
{
    if ((*curr_l)->type == 6)
    {
        if ((*curr_l)->next && (*curr_l)->next->type == 1)
        {
            *curr_l = (*curr_l)->next;
            add_to_arr(&cmd->outfile, (*curr_l)->str);
            add_to_arr(&cmd->append_re, (*curr_l)->str);
        }
        else
            perror("no outfile for append"); //need to change to error handling later
    }
}

void handle_heredoc(t_lexer **curr_l, t_cmd *cmd)
{
    if ((*curr_l)->type == 5)
    {
        if ((*curr_l)->next && (*curr_l)->next->type == 1)
        {
            *curr_l = (*curr_l)->next;
            cmd->hdoc_delimeter = ft_strdup((*curr_l)->str);
        }
    else
        perror("no hdoc delimiter"); //need to change to error handling later
    }
}

void parsing(t_lexer **lexer, t_cmd **cmds)
{
    int     i;
    int     arg_count;
    t_lexer *curr_l;
    char    **arr;
    t_cmd   *cmd;

    curr_l = *lexer;
    while (curr_l)
    {
        arg_count = cal_arg_count(curr_l);
        arr = ft_calloc(arg_count + 1, sizeof(char *));
        i = 0;
        cmd = new_cmd(arr);
        while (curr_l && curr_l->type != 2)
        {
            if (curr_l->type == 3 || curr_l->type == 4)
                handle_redirection(&curr_l, cmd);
            else if (curr_l->type == 5)
                handle_heredoc(&curr_l, cmd);
            else if (curr_l->type == 6)
                handle_append(&curr_l, cmd);
            else
                arr[i++] = ft_strdup(curr_l->str);
            curr_l = curr_l->next;
        }
        cmd_add_back(cmds, cmd);
        if (curr_l)
            curr_l = curr_l->next;
    }
    check_builtins(cmds);
    free_lexer(lexer);
}
