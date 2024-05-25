# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ting <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/16 17:33:51 by ting              #+#    #+#              #
#    Updated: 2024/03/08 14:28:17 by ting             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_isalpha.c \
      ft_memchr.c ft_memset.c \
      ft_strlcpy.c ft_strrchr.c \
      ft_bzero.c ft_isascii.c \
      ft_memcmp.c ft_strchr.c \
      ft_strlen.c ft_tolower.c \
      ft_calloc.c ft_isdigit.c \
      ft_memcpy.c ft_strdup.c \
      ft_strncmp.c ft_toupper.c \
      ft_isalnum.c ft_isprint.c \
      ft_memmove.c ft_strlcat.c \
      ft_strnstr.c ft_putchar_fd.c \
      ft_putstr_fd.c ft_putendl_fd.c\
      ft_putnbr_fd.c ft_substr.c \
      ft_strjoin.c ft_strtrim.c \
      ft_strmapi.c ft_striteri.c \
      ft_split.c ft_itoa.c \
      ft_printf.c ft_prtchar_printf.c \
      ft_prthex_printf.c ft_prtnbr_printf.c \
      ft_prtstr_printf.c ft_prtunnbr_printf.c \
      ft_strcmp.c ft_atol.c \
      ft_nb_abs.c
    

BNS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
	  ft_lstsize_bonus.c ft_lstlast_bonus.c \
	  ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	  ft_lstclear_bonus.c ft_lstiter_bonus.c \
	  ft_lstmap_bonus.c

CC = clang

FLAGS = -Wall -Wextra -Werror

HEADER = libft.h

OBJ = $(SRC:.c=.o)

BNS_OBJ = $(BNS_SRC:.c=.o)

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJ)

bonus:  @$(NAME)
	@$(CC) $(FLAGS) -c $(BNS_SRC)
	@ar rc $(NAME) $(BNS_OBJ)

clean:
	@rm -rf $(OBJ) $(BNS_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
