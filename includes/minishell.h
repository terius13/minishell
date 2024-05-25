/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:12:23 by ting              #+#    #+#             */
/*   Updated: 2024/05/25 21:51:03 by ting             ###   ########.fr       */
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

#endif