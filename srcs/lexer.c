/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:48 by ting              #+#    #+#             */
/*   Updated: 2024/07/05 20:00:16 by asyed            ###   ########.fr       */
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
		print_error("syntax error");
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

int	skip_wp(char *str, int *i)
{
	while (ft_isspace(str[*i]))
		(*i)++;
	return (*i);
}

int	tokenizer(t_lexer **lexer, char *str)
{
	int	start;
	int	i;

	i = 0;
	while (str[i])
	{
		start = skip_wp(str, &i);
		while (str[i] && !ft_isspace(str[i]) && !is_special_char(str[i]))
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				i = quotes_token(str, i);
				if (i == -1)
					return (1);
			}
			else
				i++;
		}
		if (i - start > 0)
			lexer_add_back(lexer, new_lexer(ft_strndup(str + start, i
						- start)));
		if (is_special_char(str[i]))
			handle_special_token(lexer, str, &i);
	}
	return (0);
}

int	lexer_and_parse(t_cmd **cmds, char *str, t_env **env_dup, t_ms_state *stat)
{
	t_lexer	**lexer;
	t_lexer	*current;
	t_lexer	*next;

	lexer = (t_lexer **)malloc(sizeof(t_lexer *));
	*lexer = NULL;
	if (tokenizer(lexer, str))
		return (free_lexer(lexer), free(lexer), 1);
	current = *lexer;
	while (current)
	{
		next = current->next;
		if (current->type == 1)
		{
			check_env_var(current, env_dup, stat);
			if (remove_quotes(current) == 1)
				del_lexer(lexer, current);
		}
		current = next;
	}
	if (parsing(lexer, cmds))
		return (free_lexer(lexer), free(lexer), 1);
	check_builtins(cmds);
	return (free_lexer(lexer), free(lexer), 0);
}
