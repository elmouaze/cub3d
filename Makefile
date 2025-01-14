# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 22:15:17 by ael-moua          #+#    #+#              #
#    Updated: 2025/01/10 04:00:44 by ael-moua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -std=c17 -Imandatory/include/ #-fsanitize=undefined

SRCS = mandatory/main.c $(wildcard mandatory/game/*.c) $(wildcard mandatory/parse/*.c)\
$(wildcard mandatory/utils/*.c) $(wildcard mandatory/parse/get_next_line/*.c)

OBJS = $(SRCS:.c=.o)
MLX_LIB = libs/libmlx42.a
GLFW_LIB = libs/libglfw3.a
FRAMEWORK =  $(MLX_LIB) $(GLFW_LIB) -O3 -g -ffast-math -Ofast -framework Cocoa -framework OpenGL -framework IOKit 

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(FRAMEWORK) -o $@ $(OBJS)
	
%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
re: clean all

.PHONY: clean