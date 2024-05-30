/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:48 by ting              #+#    #+#             */
/*   Updated: 2024/05/28 19:10:15 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
sudo:
Separate by '32' whitespace '9' tab;
store in lexor struct; (char *str)(t_lexor *next, *prev)
seperate by pipes
check for redirection and builtins
join the lexor string into 1 cmd char **str
*/
//cmd: |,<,>,<<,>>,
t_lexer	*new_lexer(char *str)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, "<") ||!ft_strcmp(str, ">")
			|| !ft_strcmp(str, "<<") || !ft_strcmp(str, ">>"))
	{
		new->type = 1;
	}
	else
	{
		new->type = 2;
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

//add the splited lexer words to t_lexer
//set the next and prev
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
		{
			current = current->next;
		}
		current->next = new;
		new->prev = current;
		new->next = NULL;
	}
}



t_lexer **parse_input(char *str) {
    t_lexer **lexer = (t_lexer **)malloc(sizeof(t_lexer *));
    *lexer = NULL;
    int start = 0, i = 0;
    char quote = '\0';

    while (str[i]) {
        // Skip initial spaces
        while (ft_isspace(str[i]))
            i++;
        start = i;
        // Handle quotes
        if (str[i] == '"' || str[i] == '\'')
		{
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
            char *token = strndup(str + start, i - start);
            lexer_add_back(lexer, new_lexer(token));
        }
    }
    return lexer;
}


/*
//if type == 2
void	expand_env_var(t_lexer *word)
{
	int	i;
	int	j;
	char	*var;
	char	*value;

	i = 0;
	j = 0;
	while(word->str[i])
	{
		if (word->str[i] == '$')
		{
			i++;
			var = ft_calloc(1, sizeof(ft_strlen(word->str[i])));
			while (word->str[i])
			{
				var[j++] = word->str[i++];
				i++;
				j++;
			}
			value = getenv(var)
		}
	}
}

void	rm_quotes(t_lexer *word)
{

}
*/
/*
*/

//if token == '|' all tokens before becomes **cmd
//skip '|'
/*
void	pipe_split(t_lexer *tokens)
{

}
*/

void	print_lexer(t_lexer **lexer)
{
    t_lexer *current = *lexer;
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
		lexer = parse_input(line);
			print_lexer(lexer);
		}
		free(line);
	}
	return (0);
}
