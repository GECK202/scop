# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 17:12:18 by vkaron            #+#    #+#              #
#    Updated: 2021/08/21 06:32:03 by vkaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

FLAGS = -Wall -Wextra -Werror

C_FILES = 	m_copy.c m_mul.c m_proj.c m_rot.c m_scale.c m_transl.c new_m.c \
			new_v.c
 
O_FILES = $(C_FILES:.c=.o)

H_DIR = -I./

NAME = libmat.a

UNAME_S := $(shell uname -s)

all: $(NAME)

$(NAME): $(O_FILES)
	ar rc $(NAME) $(O_FILES)
	ranlib $(NAME)

%.o: %.c libft.h
	gcc	$(FLAGS)  -c $< $(H_DIR)

clean:
	rm -f $(O_FILES)

fclean : clean
	rm -f $(NAME)

re: fclean all
