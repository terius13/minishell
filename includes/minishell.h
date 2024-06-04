/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:12:23 by ting              #+#    #+#             */
/*   Updated: 2024/06/04 12:07:15 by asyed            ###   ########.fr       */
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
# define MALLOC_ERROR 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

void	execute_builtins(char **args, char *input, t_env **env_dup);

void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_cd(char **args);
void	builtin_exit(char **args, char *input, t_env **env);

// export
void	update_current_export(t_env *tmp, char *key, char *value);
int		export_error_check(char *args);
void	assign_key_value(char **args, int equal, char **key, char **value);
void	builtin_export(char **args, t_env **env_list);

// unset

// env
void	builtin_env(t_env **env_list);
void	print_env_var(void *env_list);
t_env	**env_error(char *message);
t_env	**init_env_copy(char **env);

// env_node_utils
void	ft_lstiter_ms(t_env *lst, void (*f)(void *));
t_env	*ft_lstnew_ms(char *key, char *value);
void	ft_lstadd_back_ms(t_env **lst, t_env *new);
void	ft_lstclear_ms(t_env **lst, void (*del)(void *));

// free
void	free_split(char **split);
void	free_current_export(t_env *tmp, char *value, char **split);
void	free_env(t_env	**env_list);
void	free_all(char **args, char *input, t_env **env_dup);

#endif

/*
typedef struct s_lexer
{
	char			*str; //have to free
	int 			type; // token/cmd(1), word(2), ""(3), ''(4)
	struct s_lexer	*next;
	struct s_lexer	*prev;

}					t_lexer;

typedef struct s_cmd
{
	char			**cmd_arr;
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
*/
