# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/26 12:20:06 by egoodale          #+#    #+#              #
#    Updated: 2018/05/30 12:48:50 by egoodale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = src/main.c src/build_files.c src/display_list.c src/display.c src/ls_sort.c src/misc.c src/display_list_lngform.c
HEADER = ./include/ft_ls 
LIBS = libftprintf/libftprintf.a
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
OBJ = $(patsubst %.c, %.o, *.c)

all: $(NAME)
$(NAME): $(OBJ)
	gcc -I $(HEADER) -g $(OBJ) -o $(NAME) $(LIBS)
$(OBJ):
	gcc -I $(HEADER) -g $(SRC) -c

clean: 
		rm -rf $(OBJ)
fclean: clean
		rm -rf $(NAME)
re: fclean all