/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:48 by ting              #+#    #+#             */
/*   Updated: 2024/05/31 22:29:57 by ting             ###   ########.fr       */
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
		printf("close quote missing");
		exit(1); //change to error handling
	}
	return (i);
}

t_lexer **tokenizer(char *str)
{
    t_lexer **lexer;
    int		start;
	int		i;
	char	*token;

	start = 0;
	i = 0;
	lexer = (t_lexer **)malloc(sizeof(t_lexer *));
	*lexer = NULL;
    while (str[i])
	{
        // Skip initial spaces
        while (ft_isspace(str[i]))
            i++;
        start = i;
        // Handle quotes
        if (str[i] == '"' || str[i] == '\'')
		{
			i = quotes_token(str, i); //skip the quote's string
        }
		else
		{
            // Non-quoted word
            while (str[i] && !ft_isspace(str[i]) && str[i] != '"' && str[i] != '\'')
                i++;
        }
        // Add the token to the lexer list
        if (i > start)
		{
            char *token = ft_strndup(str + start, i - start);
            lexer_add_back(lexer, new_lexer(token));
        }
    }
    return lexer;
}

//need to simplify, make neater
void	replace_env_var(t_lexer *lexer, int var_start, int var_len, char *value)
{
	char	*old_str;
	char	*new_str;
	int		str_len;
	int		i;
	int		back_len;


	str_len = (ft_strlen(lexer->str) - (var_len + 1)) + ft_strlen(value);
	old_str = ft_strdup(lexer->str);
	new_str = (char *)malloc(sizeof(char) * str_len + 1);
	back_len = ft_strlen(old_str) - var_start - var_len - 2;

	ft_strlcpy(new_str, old_str, var_start + 1);
	ft_strlcat(new_str, value, ft_strlen(new_str) + ft_strlen(value) + 1);
	if(ft_strlen(new_str) != str_len)
	{
		ft_strlcat(new_str, old_str + var_start + var_len + 1, ft_strlen(new_str) + back_len + 2);
	}
	printf("env str: %s\n", new_str);

	free(lexer->str);
	lexer->str = new_str;
	free(old_str);
}

int		cal_var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '"' && str[i] != '\'' && str[i] != '$')
		i++;
	return (i);
}

//if type == 2
//will need to change later on the getenv from own env struct
//create own getenv function
void	expand_env_var(t_lexer **lexer)
{
	int		i;
	char	*var;
	int		var_len;
	char	*value;
	t_lexer *current;

	current = *lexer;
	while (current)
	{
		//if type 2
		i = 0;
		while (current->str[i])
		{
			if (current->str[i] == '$')
			{
				i++;
				var_len = cal_var_len(current->str + i);
				var = (char *)malloc(sizeof(char) * var_len);
				ft_strlcpy(var, current->str + i, var_len + 1); //cpy the varname to var
				printf("%s, %d\n", var, var_len);
				value = getenv(var);
				printf("The value: %s\n", value);
				replace_env_var(current, i - 1, var_len, value);
			}
			i++;
		}
		current = current->next;
	}
}
/*
void	rm_quotes(t_lexer *word)
{
	i++ to the next quote
	strdup everything inbetween
}
*/


void	print_lexer(t_lexer **lexer)
{
    t_lexer *current;

	current = *lexer;
    while (current)
    {
        printf(G "Token: %s " RST, current->str);
		printf(M "Type: %d\n" RST, current->type);
        current = current->next;
    }
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_lexer **lexer;

	while (1)
	{
		line = readline(C "shell@st42:$ " RST);
		if (line)
		{
		//	lexer = wp_split(line);
		lexer = tokenizer(line);
		print_lexer(lexer);
		//if lexer while loop to expand str
		//have to check if it double quotes then enter expand
		expand_env_var(lexer);
		print_lexer(lexer);
		}
		free(line);
	}
	return (0);
}
