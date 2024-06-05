/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:48 by ting              #+#    #+#             */
/*   Updated: 2024/06/05 17:20:02 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

// Main tokenizer function
void tokenizer(t_lexer **lexer, char *str)
{
    int start;
    int i = 0;
    int token_len;

    while (str[i])
	{
        while (ft_isspace((unsigned char)str[i]))
            i++;
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
                break;
			else
                i++;
        }
        // Create a token for the word if it exists
        token_len = i - start;
        if (token_len > 0)
            lexer_add_back(lexer, new_lexer(ft_strndup(str + start, token_len)));
        // Handle special characters separately
        if (is_special_char(str[i]))
		{
            if (str[i] == '<' || str[i] == '>')
			{
                int j = i;
                j++;
                if (str[j] == str[i])
                    j++;
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

void	lexical_analysis(t_lexer **lexer, char *str)
{
	t_lexer	*current;
	int		no_value;

	tokenizer(lexer, str);
//	print_lexer(lexer);
	current = *lexer;
	while (current)
	{
		if (current->type == 1)
		{
			check_env_var(current);
			no_value = remove_quotes(current);
			if (no_value)
				del_lexer(lexer, current);
		}
		current = current->next;
	}
}
