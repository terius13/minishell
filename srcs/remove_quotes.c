/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:45:07 by ting              #+#    #+#             */
/*   Updated: 2024/06/12 19:34:20 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	remove_quotes(t_lexer *lexer)
{
    int		i;
    int		j;
    char	*new_str;
    char	*old_str;
    char	quote_char;

    old_str = lexer->str;
    new_str = malloc(ft_strlen(old_str) + 1);
    if (!new_str)
        return 1;
    i = 0;
    j = 0;
    quote_char = '\0';
    while (old_str[i])
    {
        if (quote_char == '\0' && (old_str[i] == '\'' || old_str[i] == '"'))
            quote_char = old_str[i]; // Opening quote detected
        else if (quote_char != '\0' && old_str[i] == quote_char)
            quote_char = '\0'; // Closing quote detected
        else
            new_str[j++] = old_str[i];
        i++;
    }
    new_str[j] = '\0';
    free(lexer->str);
    lexer->str = new_str;
    if (ft_strlen(new_str) == 0)
        return 1;
    return 0;
}
