# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 22:15:17 by ael-moua          #+#    #+#              #
#    Updated: 2024/11/20 11:47:09 by ael-moua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror  -std=c17

SRCS = main.c $(wildcard srcs/*.c) $(wildcard PARSE/*.c) $(wildcard PARSE/utils/*.c) $(wildcard PARSE/gnl/*.c)

OBJS = $(SRCS:.c=.o)
MLX_LIB = libs/libmlx42.a
GLFW_LIB = libs/libglfw3.a
FRAMEWORK =  $(MLX_LIB) $(GLFW_LIB) -O3 -g -ffast-math -Ofast -framework Cocoa -framework OpenGL -framework IOKit 

NAME = cube3d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(FRAMEWORK) -o $@ $(OBJS)
	
%.o: %.c cube3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
re: clean all

.PHONY: clean