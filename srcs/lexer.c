/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:48 by ting              #+#    #+#             */
/*   Updated: 2024/06/12 20:18:56 by ting             ###   ########.fr       */
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
		perror("close quote missing");
		return (-1);
	}
	return (i);
}

void	handle_special_token(t_lexer **lexer, char *str, int *i)
{
	int	j;

	if (str[*i] == '<' || str[*i] == '>')
	{
		j = *i;
		j++;
		if (str[j] == str[*i])
			j++;
		lexer_add_back(lexer, new_lexer(ft_strndup(str + *i, j - *i)));
		*i = j;
	}
	else
	{
		lexer_add_back(lexer, new_lexer(ft_strndup(str + *i, 1)));
		(*i)++;
	}
}

int	tokenizer(t_lexer **lexer, char *str)
{
	int	start;
	int	i;
	int	token_len;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		start = i;
		while (str[i] && !ft_isspace(str[i]) && !is_special_char(str[i]))
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				if ((i = quotes_token(str, i)) == -1)
					return (1);
			}
			else
				i++;
		}
		token_len = i - start;
		if (token_len > 0)
			lexer_add_back(lexer, new_lexer(ft_strndup(str + start,
						token_len)));
		if (is_special_char(str[i]))
			handle_special_token(lexer, str, &i);
	}
	return (0);
}

int	lexer_and_parse(t_cmd **cmds, char *str)
{
	t_lexer	**lexer;
	t_lexer	*current;
	t_lexer	*next;
	int		no_value;

	lexer = (t_lexer **)malloc(sizeof(t_lexer *));
	*lexer = NULL;
	if (tokenizer(lexer, str))
        return (free_lexer(lexer), free(lexer), 1);
	current = *lexer;
	while (current)
	{
		next = current->next; // Store the next node before any potential deletion
		if (current->type == 1)
		{
			check_env_var(current);
			no_value = remove_quotes(current);
			if (no_value)
				del_lexer(lexer, current);
		}
		current = next;
	}
	printf("After lexer:\n");
	print_lexer(lexer);
	if (parsing(lexer, cmds))
        return (free_lexer(lexer), free(lexer), 1);
	check_builtins(cmds);
	print_parse(cmds);
	free_lexer(lexer);
	free(lexer);
	return (0);
}
