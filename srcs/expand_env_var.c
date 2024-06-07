/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:16:27 by ting              #+#    #+#             */
/*   Updated: 2024/06/06 18:14:25 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	replace_env_var(t_lexer *lexer, int var_start, int var_len, char *value)
{
    char	*old_str;
	char	*new_str;
    int     new_str_len;
    int		back_len;
    int     mid_len;

    old_str = ft_strdup(lexer->str);
    mid_len = var_start + var_len + 1; //until after the var
    back_len = ft_strlen(old_str) - var_start - (var_len + 1);// +1 for '\0' in strcat
    new_str_len = (ft_strlen(old_str) - (var_len + 1)) + ft_strlen(value);
    new_str = (char *)malloc(sizeof(char) * new_str_len + 1);

    ft_strlcpy(new_str, old_str, var_start + 1); //cpy the front of the old str
    if (*value != '\0')
    {
        ft_strlcat(new_str, value, ft_strlen(new_str) + ft_strlen(value) + 1); //concat the value
    }
    ft_strlcat(new_str, old_str + mid_len, new_str_len + back_len + 1); //concat after the value
    free(lexer->str);
	lexer->str = new_str;
	free(old_str);
}

int		cal_var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '"' && str[i] != '\'' && str[i] != '$' && str[i] != ' ')
		i++;
	return (i);
}

int    expand_env_var(t_lexer *lexer, int i)
{
    char    *var;
    int     var_len;
    char    *value;

//    if(!ft_strcmp(value, "?"))
//        handle_expand_question_mark();
    var_len = cal_var_len(lexer->str + i);
    var = (char *)malloc(sizeof(char) * (var_len + 1));
    ft_strlcpy(var, lexer->str + i, var_len + 1); // Copy the varname to var
    value = getenv(var); //must use own getenv()
    free(var);
    if (value == NULL)
    {
        value = ft_calloc(1, 1);
        *value = '\0';
    }
    replace_env_var(lexer, i - 1, var_len, value);
    i += ft_strlen(value) - 1; // Adjust index to skip the expanded value
    if (*value == '\0')
        free(value);
    return (i);
}

void check_env_var(t_lexer *lexer)
{
    t_lexer *current;
    int        i;
    char    quote;

    current = lexer;
    if (current->type == 1)
    {
        i = 0;
        quote = '\0';
        while (current->str[i])
        {
            if (current->str[i] == '\'' && quote == '\0')
                quote = '\''; // Entering single quote mode
            else if (current->str[i] == '\'' && quote == '\'')
                quote = '\0'; // Exiting single quote mode
            else if (current->str[i] == '"' && quote == '\0')
                quote = '"'; // Entering double quote mode
            else if (current->str[i] == '"' && quote == '"')
                quote = '\0'; // Exiting double quote mode
            if (current->str[i] == '$' && quote != '\'')
                i = expand_env_var(lexer, i + 1);
            else
                i++;
        }
    }
}

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
    // If the new string is empty, return 1 to indicate that the node should be deleted
    if (ft_strlen(new_str) == 0)
        return 1;
    return 0;
}



