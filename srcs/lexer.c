/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:48 by ting              #+#    #+#             */
/*   Updated: 2024/06/05 14:57:51 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Type 1:string, type 2:'|', type 3:'<'
//Type 4:'>', Type 5:'<<', type 6:'>>'
t_lexer	*new_lexer(char *str)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!ft_strcmp(str, "|"))
		new->type = 2;
	else if (!ft_strcmp(str, "<"))
		new->type = 3;
	else if (!ft_strcmp(str, ">"))
		new->type = 4;
	else if (!ft_strcmp(str, "<<"))
		new->type = 5;
	else if (!ft_strcmp(str, ">>"))
		new->type = 6;
	else
		new->type = 1; //type 1 is string
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
int is_special_char(char c)
{
    return (c == '<' || c == '>' || c == '|');
}

// Main tokenizer function
void tokenizer(t_lexer **lexer, char *str)
{
    int start;
    int i = 0;
    int token_len;

    while (str[i])
	{
        while (ft_isspace((unsigned char)str[i]))
		{
            i++;
        }
        start = i;
        while (str[i] && !ft_isspace((unsigned char)str[i]))
		{
            if (str[i] == '"' || str[i] == '\'')
			{
                i = quotes_token(str, i);
                if (i == -1)
				{
                    free_all(lexer, NULL);
                    return; // Exit on error
                }
            }
			else if (is_special_char(str[i]))
			{
                break;
            }
			else
			{
                i++;
            }
        }
        // Create a token for the word if it exists
        token_len = i - start;
        if (token_len > 0)
		{
            lexer_add_back(lexer, new_lexer(ft_strndup(str + start, token_len)));
        }
        // Handle special characters separately
        if (is_special_char(str[i]))
		{
            if (str[i] == '<' || str[i] == '>')
			{
                int j = i;
                j++;
                if (str[j] == str[i])
				{
                    j++;
                }
                lexer_add_back(lexer, new_lexer(ft_strndup(str + i, j - i)));
                i = j;
            }
			else
			{
                lexer_add_back(lexer, new_lexer(ft_strndup(str + i, 1)));
                i++;
            }
        }
    }
}


/*
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
*/

void	del_lexer(t_lexer **lexer, t_lexer *to_del)
{
    if (to_del->prev)
        to_del->prev->next = to_del->next;
    else
        *lexer = to_del->next;
    if (to_del->next)
        to_del->next->prev = to_del->prev;
    free(to_del->str);
    free(to_del);
}

void	lexical_analysis(t_lexer **lexer, char *str)
{
	t_lexer	*current;
	int		checker;

	tokenizer(lexer, str);
//	print_lexer(lexer);
	current = *lexer;
	while (current)
	{
		if (current->type == 1)
		{
			check_env_var(current);
			checker = remove_quotes(current);
			if (checker)
				del_lexer(lexer, current);
		}
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
