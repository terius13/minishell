/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:16:27 by ting              #+#    #+#             */
/*   Updated: 2024/06/01 21:49:13 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
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
        ft_strlcat(new_str, value, ft_strlen(new_str) + ft_strlen(value) + 1); //concat the value
    ft_strlcat(new_str, old_str + mid_len, new_str_len + back_len + 1); //concat after the value
    free(lexer->str);
	lexer->str = new_str;
	free(old_str);
}
*/

void replace_env_var(t_lexer *lexer, int var_start, int var_len, char *value)
{
    char *old_str = lexer->str;
    int old_len = strlen(old_str);
    int value_len = strlen(value);
    int new_len = old_len - var_len + value_len;

    char *new_str = (char *)malloc(new_len + 1);
    if (!new_str) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strncpy(new_str, old_str, var_start);  // Copy part before the variable
    strcpy(new_str + var_start, value);    // Replace variable with value
    strcpy(new_str + var_start + value_len, old_str + var_start + var_len + 1);  // Copy the rest

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


void    expand_env_var(t_lexer *lexer, int flag)
{
    int		i;
	char	*var;
	int		var_len;
	char	*value;
	t_lexer *current;

    i = 0;
    current = lexer;
    while (current->str[i])
    {
        if (current->str[i] == '$' && flag > 0)
        {
            flag--;
        //    i++;
        }
        if (current->str[i] == '$' && flag == 0) //can comment out later cause 1st will always be $
    	{
            i++;
	    	var_len = cal_var_len(current->str + i);
    		var = (char *)malloc(sizeof(char) * var_len + 1);
    		ft_strlcpy(var, current->str + i, var_len + 1); //cpy the varname to var
            value = getenv(var);
            free(var);
    		if (value == NULL)
    		{
	    		value = ft_calloc(1, 1);
	    		*value = '\0';
	    	}
	    	replace_env_var(lexer, i - 1, var_len, value);
            //if i dont break here, it keeps going here in a loop
            //not even going back to check_env_var
            //maybe i have to combine the two function then figure out how to seperate
            i += strlen(value) - 1;
        //    break;
        //    i += ft_strlen(value) - 1;
        }
        i++;
    }
}

void check_env_var(t_lexer **lexer)
{
    t_lexer *current;
    int        i;
    char    quote;
    int     flag;

    flag = 0;
    current = *lexer;
    while (current) {
        if (current->type == 1) {
            i = 0;
            quote = '\0';
            while (current->str[i]) {
                if (current->str[i] == '\'' && quote == '\0')
                {
                    printf("Entering single quote mode\n");
                    quote = '\''; // Entering single quote mode
                } else if (current->str[i] == '\'' && quote == '\'') {
                    quote = '\0'; // Exiting single quote mode
                } else if (current->str[i] == '"' && quote == '\0') {
                    quote = '"'; // Entering double quote mode
                } else if (current->str[i] == '"' && quote == '"') {
                    quote = '\0'; // Exiting double quote mode
                }
                if (current->str[i] == '$' && quote == '\'')
                {
                    flag++;
                }
                if (current->str[i] == '$' && quote != '\'')
                {
                    printf("flag: %d\n", flag);
                    expand_env_var(current, flag); // Call expand_env_var if $ is outside single quotes
                    print_lexer(lexer);
                    printf("quote: %c\n", quote);
                    printf("i = %d\n", i);
                    i = -1;
                }
                i++;
            }
        }
        current = current->next;
    }
}


