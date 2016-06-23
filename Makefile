# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simzam <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/10 09:17:10 by simzam            #+#    #+#              #
#    Updated: 2016/06/23 14:47:55 by jomeirin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = wolf3d

FLAG = -Wall -Wextra -g

SRC = src/wolf3d.c src/get_next_line.c src/draw.c src/raycast.c src/controls.c

RM = rm -f

MLX = -lmlx -framework OpenGL -framework AppKit 

INC = -I /usr/include/X11

LIBFT = -lm -Llibft -lft

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re


all: $(NAME)

%.o: %.c
	@$(CC) $(FLAG) -c -o $@ $^ $(INC)

$(NAME): $(OBJ)
		@cd libft/ && make -s
		@$(CC) $(FLAG) $(OBJ) -o $(NAME) $(INC) $(MLX) $(LIBFT) 

clean:
		@$(RM) $(OBJ)
		@cd libft/ && make -s clean

fclean: clean
		@$(RM) $(NAME)
		@cd libft/ && make -s fclean

re: fclean all

.PHONY: all clean fclean re
