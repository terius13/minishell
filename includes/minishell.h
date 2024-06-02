/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:12:23 by ting              #+#    #+#             */
/*   Updated: 2024/06/02 16:46:15 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>  //for history handling
# include <readline/readline.h> //for command line input
# include <stdio.h>
	//for standard input/output and memory management
# include <stdlib.h>
	//for standard input/output and memory management
# include <string.h>            //for string manipulation
# include <sys/types.h>         //for process management
# include <sys/wait.h>          //for process management
# include <unistd.h>            //POSIX API functions

# define G "\033[32m"
# define M "\033[35m"
# define C "\033[36m"
# define RST "\033[0m"


typedef struct s_lexer
{
	char			*str; //have to free
	int 			type; // token/cmd(1), word(2), ""(3), ''(4)
	struct s_lexer	*next;
	struct s_lexer	*prev;

}					t_lexer;

typedef struct s_cmd
{
	char			**cmd;
	int				in_pid;
	int				out_pid;
	char			*infile;
	char			*outfile;
	int				*builtin;
}					t_cmd;

//lexer.c
t_lexer	*new_lexer(char *str);
void	lexer_add_back(t_lexer **lexer, t_lexer *new);
int		quotes_token(char *str, int i);
void	tokenizer(t_lexer **lexer, char *str);
void	lexical_analysis(t_lexer **lexer, char *str);
void	print_lexer(t_lexer **lexer); //to delete later

//expand_env_var.c
void	replace_env_var(t_lexer *lexer, int var_start, int var_len, char *value);
int		cal_var_len(char *str);
int		expand_env_var(t_lexer *lexer, int i);
void 	check_env_var(t_lexer *lexer);

//free_for_lexer.c
void 	free_lexer(t_lexer **lexer);
void	free_all(t_lexer **lexer, char *line);

#endif
