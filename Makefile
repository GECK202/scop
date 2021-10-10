# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#              #
#    Updated: 2021/08/21 06:50:37 by vkaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, libr

PROGRAM_NAME = scop

FLAGS =	-Wall -Wextra -Werror -g

FILES =		main \
			matrix \
			error \
			shader \
			texture \
			utils \
			window_events \
			gl_objs \
			init \
			model \
			store \
			parse

S_DIR =		src

O_DIR =		obj

H_DIR =		include

O_FILES =	$(addprefix $(O_DIR)/, $(addsuffix .o, $(FILES)))

H_FILE =	$(H_DIR)/scop.h

LIBS =		-L./libs/libft -lft\
			-L./libs/libmat -lmat\
			-L./libs/glad/ -lglad\
			-L./libs/glfw -lglfw3\

H_FIND =	-I ./include \
			-I ./libs/libft \
			-I ./libs/libmat \
			-I ./libs/glad \
			-I ./libs/glfw

FRAME =		-framework Cocoa -framework OpenGL -framework IOKit \

all: libft libmat $(PROGRAM_NAME)

libft:
	make -C libs/libft/ all

libmat:
	make -C libs/libmat/ all

$(PROGRAM_NAME): $(O_FILES)
	gcc $(FLAGS) -o $@ $^ $(LIBS) $(FRAME)

$(O_DIR)/%.o: $(S_DIR)/%.c $(H_FILE)
	mkdir -p $(O_DIR)
	gcc $(FLAGS) -c $< -o $@ $(H_FIND)

clean:
	make -C libs/libft/ clean
	make -C libs/libmat/ clean
	rm -rf $(O_DIR)

fclean : clean
	make -C libs/libft/ fclean
	make -C libs/libmat/ fclean
	rm -f $(PROGRAM_NAME)

re: fclean all

