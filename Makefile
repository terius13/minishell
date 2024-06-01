# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asyed <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 16:11:35 by ting              #+#    #+#              #
#    Updated: 2024/06/01 16:34:17 by asyed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

LIBFT = libft/libft.a

SRCSPATH = srcs/

SRCS = minishell.c builtins_env_node_utils.c builtins_env.c\
		builtins_utils.c builtins.c del_and_free.c

OBJS = $(addprefix $(SRCSPATH), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
		@$(MAKE) -C libft
		@cc $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
		

clean: 
		@$(MAKE) clean -C libft
		@$(RM) $(OBJS)	

fclean: clean
		@$(MAKE) fclean -C libft
		@$(RM) $(NAME)

re: fclean all

.phony: all clean fclean re