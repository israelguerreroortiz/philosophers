# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iisraa11 <iisraa11@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/03 12:11:13 by iisraa11          #+#    #+#              #
#    Updated: 2025/10/23 15:08:47 by iisraa11         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
CC = cc
FLAGS = -Wall -Wextra -Werror

SRC = src/philosophers.c src/data_init.c src/dinner.c src/utils.c src/routine.c src/monitor.c

OBJ := build/philosophers.o build/data_init.o build/dinner.o build/utils.o build/routine.o build/monitor.o

all: build $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -I./includes -o $@

build:
	mkdir -p build

build/%.o: src/%.c
	$(CC) $(FLAGS) -I./includes -c $< -o $@

clean:
	rm -rf build/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re build
