# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 22:15:17 by ael-moua          #+#    #+#              #
#    Updated: 2024/11/19 03:56:20 by ael-moua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

SRCS = $(wildcard *.c) $(wildcard utils/*.c) $(wildcard gnl/*.c)

OBJS = $(SRCS:.c=.o)

NAME = cube3d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	make clean
%.o: %.c cube3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
re: clean all

.PHONY: clean