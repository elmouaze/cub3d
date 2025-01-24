# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 22:15:17 by ael-moua          #+#    #+#              #
#    Updated: 2025/01/24 10:16:10 by abennar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -I mandatory/include/ #-fsanitize=address

SRCS =	.//mandatory/game/error_handling.c \
		.//mandatory/game/game.c \
		.//mandatory/game/hooks.c \
		.//mandatory/game/horizontal.c \
		.//mandatory/game/memory.c \
		.//mandatory/game/raycasting.c \
		.//mandatory/game/textures.c \
		.//mandatory/game/vertical.c \
		.//mandatory/main.c \
		.//mandatory/parse/get_next_line/get_next_line.c \
		.//mandatory/parse/get_next_line/get_next_line_utils.c \
		.//mandatory/parse/map.c \
		.//mandatory/parse/map_utils.c \
		.//mandatory/parse/memory_and_errors.c \
		.//mandatory/parse/parse.c \
		.//mandatory/utils/ft_atoi.c \
		.//mandatory/utils/ft_calloc.c \
		.//mandatory/utils/ft_itoa.c \
		.//mandatory/utils/ft_memset.c \
		.//mandatory/utils/ft_split.c \
		.//mandatory/utils/ft_strlcpy.c \
		.//mandatory/utils/ft_strlen.c \
		.//mandatory/utils/ft_strncmp.c \
		.//mandatory/utils/ft_strtrim.c \
		.//mandatory/utils/ft_substr.c \


OBJS = $(SRCS:.c=.o)
MLX_LIB  = libs/libmlx42.a
GLFW_LIB = libs/libglfw3.a
FRAMEWORK =  $(MLX_LIB) $(GLFW_LIB) -framework Cocoa -framework OpenGL -framework IOKit 

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