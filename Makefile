# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/16 17:31:02 by egoodale          #+#    #+#              #
#    Updated: 2018/05/17 16:54:33 by egoodale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = 	src/main.c src/check_args.c
HEADER = ./include/ft_ls.h
OBJ = $(patsubst %.c, %.o, *.c)
all: $(NAME)
$(NAME): $(OBJ)
	gcc -I $(HEADER) -g $(OBJ) -o $(NAME)
$(OBJ):
	gcc -I $(HEADER) -g $(SRC) -c

clean: 
		rm -rf $(OBJ)
fclean: clean
		rm -rf $(NAME)
re: fclean all


