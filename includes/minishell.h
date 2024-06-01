/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:12:23 by ting              #+#    #+#             */
/*   Updated: 2024/06/01 19:27:08 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>  //for history handling
# include <readline/readline.h> //for command line input
# include <stdio.h>
// for standard input/output and memory management
# include <stdlib.h>
// for standard input/output and memory management
# include <string.h>    //for string manipulation
# include <sys/types.h> //for process management
# include <sys/wait.h>  //for process management
# include <unistd.h>    //POSIX API functions

# define G "\033[32m"
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
void	builtin_export(char **args, t_env **env_list);

// export
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
void	del_env_var(void *env_list);
void	free_env(t_env	**env_list);
void	free_all(char **args, char *input, t_env **env_dup);

#endif
