/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:21:41 by ting              #+#    #+#             */
/*   Updated: 2024/06/08 13:09:24 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_env(t_env	**env_list)
{
	t_env	*tmp;
	t_env	*next;

	if (env_list == NULL || *env_list == NULL)
		return ;
	tmp = *env_list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key)
		{
			free(tmp->key);
			tmp->key = NULL;
		}
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		free(tmp);
		tmp = next;
	}
	*env_list = NULL;
	//free(env_list);
}

void free_lexer(t_lexer **lexer)
{
    t_lexer *current;
    t_lexer *next;

    if (!lexer || !*lexer)
        return;
    current = *lexer;
    while (current)
	{
        next = current->next;
        free(current->str);
        free(current);
        current = next;
    }
    *lexer = NULL;
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd *current;
    t_cmd *next;
	int	i;

	i = 0;
    if (!cmds || !*cmds)
        return;
    current = *cmds;
    while (current)
	{
        next = current->next;
		i = 0;

		//change the while loop to free_array function
        while (current->cmd_arr[i])
		{
			free(current->cmd_arr[i]);
			i++;
		}
		free(current->cmd_arr);
		if (current->hdoc_delimeter)
			free(current->hdoc_delimeter);
        if (current->infile)
            free(current->infile);
        if (current->outfile)
        free(current->outfile);
        free(current);
        current = next;
    }
    *cmds = NULL;
}
/*
freeall_and_exit(t_cmd **cmds)
{

}
*/

/*
void	freeall_and_exit(t_lexer **lexer, t_cmd **cmds, char *line) //take out lexer and line
{
	if (*lexer)
		free_lexer(lexer);
	if (lexer)
		free(lexer);
    if (*cmds)
        free_cmds(cmds);
    if (cmds)
    {
        free(cmds);
    }
	if (line)
		free(line);
//	exit(1); //need to exit so the func that called this with error dont continue running
}*/
