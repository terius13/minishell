/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:45:07 by ting              #+#    #+#             */
/*   Updated: 2024/07/05 20:43:40 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*detect_quotes(char *old_str, char *new_str)
{
	char	quote_char;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote_char = '\0';
	while (old_str[i])
	{
		if (quote_char == '\0' && (old_str[i] == '\'' || old_str[i] == '"'))
			quote_char = old_str[i];
		else if (quote_char != '\0' && old_str[i] == quote_char)
			quote_char = '\0';
		else
			new_str[j++] = old_str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

// int	remove_quotes(t_lexer *lexer)
// {
// 	char	*new_str;
// 	char	*old_str;

// 	old_str = lexer->str;
// 	new_str = malloc(ft_strlen(old_str) + 1);
// 	if (!new_str)
// 		return (1);
// 	new_str = detect_quotes(old_str, new_str);
// 	free(lexer->str);
// 	lexer->str = new_str;
// 	if (ft_strlen(new_str) == 0)
// 		return (1);
// 	return (0);
// }

int remove_quotes(t_lexer *lexer)
{
    char *new_str;
    char *old_str;

    old_str = lexer->str;
    new_str = malloc(ft_strlen(old_str) + 1);
    if (!new_str)
        return 1;
    new_str = detect_quotes(old_str, new_str);
    free(lexer->str);
    lexer->str = new_str;
    if (ft_strlen(new_str) == 0)
    {
        free(new_str);
        lexer->str = NULL; // Set the string to NULL to indicate it's empty
        return 1;
    }
    return 0;
}
