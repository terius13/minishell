# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/16 17:33:51 by ting              #+#    #+#              #
#    Updated: 2024/06/06 12:07:58 by ting             ###   ########.fr        #
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
      ft_nb_abs.c ft_lstnew.c \
      ft_lstadd_front.c ft_lstsize.c \
      ft_lstlast.c ft_lstadd_back.c \
      ft_lstdelone.c ft_lstclear.c \
      ft_lstiter.c ft_lstmap.c \
	ft_isspace.c ft_strndup.c \

CC = clang

FLAGS = -Wall -Wextra -Werror

HEADER = libft.h

OBJ = $(SRC:.c=.o)

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		@ar rcs $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
