/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:12:23 by ting              #+#    #+#             */
/*   Updated: 2024/05/28 18:59:01 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h> //for standard input/output and memory management
# include <stdlib.h> //for standard input/output and memory management
# include <unistd.h> //POSIX API functions
# include <string.h> //for string manipulation
# include <sys/types.h> //for process management
# include <sys/wait.h> //for process management
# include <readline/readline.h> //for command line input
# include <readline/history.h> //for history handling

# define G "\033[32m"
# define C "\033[36m"
# define RST "\033[0m"

void	execute_builtins(char **args, char *input, char **env);
void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_cd(char **args);

// export

// unset


void	builtin_env(char **env);
void	builtin_exit(char **args, char *input);
void	free_all(char **args, char *input);

#endif