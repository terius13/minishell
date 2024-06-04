/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:09:03 by ting              #+#    #+#             */
/*   Updated: 2024/06/04 17:06:56 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//split by pipes first then remove quotes
//should only remove the first quote

int	remove_quotes(t_lexer *lexer)
{
    int		i;
    int		j;
    char	*new_str;
    char	*old_str;

    old_str = lexer->str;
    new_str = malloc(strlen(old_str) + 1); // Allocate enough space for the new string

    if (!new_str)
        return 1;

    i = 0;
    j = 0;
    while (old_str[i])
    {
        // If the character is not a quote, copy it to the new string
        if (old_str[i] != '\'' && old_str[i] != '"')
        {
            new_str[j] = old_str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0'; // Null-terminate the new string

    free(lexer->str);
    lexer->str = new_str;

    // If the new string is empty, return 1 to indicate that the node should be deleted
    if (strlen(new_str) == 0)
        return 1;

    return 0;
}
/*
int	remove_quotes(t_lexer *lexer)
{
	int		i;
	int		j;
	char	quote;
	char	*new_str;
	int		new_str_len;
	char	*old_str;

	i = 0;
	old_str = ft_strdup(lexer->str);
	new_str_len = ft_strlen(old_str) - 2;

	if (ft_strlen(old_str) == 0)
	{
		return (1);
	}

	while (old_str[i] && old_str[i] != '\'' && old_str[i] != '"')
	{
		i++;
	}
	new_str = (char *)malloc(sizeof(char) * new_str_len);
	if (old_str[i] != '\0')
		quote = old_str[i];
	if (i != 0)
	{
		ft_strlcpy(new_str, old_str + i, i);
	}
	i++;
	j = i;
	while (old_str[j] && old_str[j] != quote)
		j++;
	ft_strlcpy(new_str, old_str + i, j - i + 1);
	j++;
	free(lexer->str);
	lexer->str = new_str;
//	free(new_str);
	return (0);
}
*/




