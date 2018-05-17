# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/16 17:31:02 by egoodale          #+#    #+#              #
#    Updated: 2018/05/16 17:49:36 by egoodale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = 	src/main.c\ 
		src/chec_args.c\
HEADER = ./include/ft_ls.h
OBJ = $(patsubst %.c, %.o, *.c)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -I $(HEADER) $(OBJ) -o $(NAME)
$(OBJ): $(SRC)
	gcc -I $(HEADER) $(SRC) -c


