/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:48 by ting              #+#    #+#             */
/*   Updated: 2024/06/01 16:05:23 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*new_lexer(char *str)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, "<<") || !ft_strcmp(str, ">>"))
		new->type = 1;
	else if (ft_strchr(str, '"') && (!ft_strchr(str, '\'') || ft_strchr(str,
				'\'') > ft_strchr(str, '"')))
		new->type = 3;
	else if (ft_strchr(str, '\'') && (!ft_strchr(str, '"') || ft_strchr(str,
			'"') > ft_strchr(str, '\'')))
		new->type = 4;
	else
		new->type = 2;
	new->next = NULL;
	new->prev = NULL;
	free(str);
	return (new);
}

// add the splited lexer words to t_lexer
// set the next and prev
void	lexer_add_back(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*current;

	if (!lexer || !new)
		return ;
	if (!*lexer)
	{
		*lexer = new;
		new->prev = NULL;
		new->next = NULL;
	}
	else
	{
		current = *lexer;
		while (current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
		new->next = NULL;
	}
}

int	quotes_token(char *str, int i)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	else if (str[i] != quote)
	{
		printf("close quote missing\n");
		return (-1); // change to error handling
	}
	return (i);
}
void	tokenizer(t_lexer **lexer, char *str)
{
    int start;
    int i;
    int token_len;

	i = 0;
    while (str[i])
	{
        while (isspace(str[i]))
            i++;
        start = i;
        while (str[i] && !isspace((unsigned char)str[i]))
		{
            if (str[i] == '"' || str[i] == '\'')
			{
                i = quotes_token(str, i);
                if (i == -1)
				{
                    return(free_all(lexer, NULL)); // Exit on error
                }
            }
			else
                i++;
        }
        token_len = i - start;
        if (token_len > 0)
            lexer_add_back(lexer, new_lexer(ft_strndup(str + start, token_len)));
    }
}


void	lexical_analysis(t_lexer **lexer, char *str)
{
	int		i;
	t_lexer	*current;

	i = 0;
	tokenizer(lexer, str);
	print_lexer(lexer);
	current = *lexer;
	while (current)
	{
		if (current->type == 2 || current->type == 3)
			expand_env_var(current);
//		if (current->type == 3 || current->type == 4)
//		{
//			printf("entering rm quotes\n");
//			remove_quotes(current);
//		}
		current = current->next;
	}
}

// delete this function later only for testing
void	print_lexer(t_lexer **lexer)
{
	t_lexer	*current;

	current = *lexer;
	while (current)
	{
		printf(G "Token: %s " RST, current->str);
		printf(M "Type: %d\n" RST, current->type);
		current = current->next;
	}
}
