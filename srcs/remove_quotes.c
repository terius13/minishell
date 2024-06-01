/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:09:03 by ting              #+#    #+#             */
/*   Updated: 2024/06/01 19:40:20 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//if type 3 & 4 then have to remove quotes
//should only remove the first quotes
/*
void    remove_quotes(t_lexer *lexer)
*/









/*
void	remove_quotes(t_lexer *lexer)
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

//	if (new_str_len == 0)
//	{
//		// nothing in quotes, need to handle, maybe set node to NULL,or remove node
//		// return ;
//	}
	
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
}
*/



