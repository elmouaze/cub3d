/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:39:14 by abennar           #+#    #+#             */
/*   Updated: 2025/01/25 11:08:08 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_MAX 2147483424

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE > BUFFER_MAX || BUFFER_SIZE <= 0
#   error "Buffer size is out of range."
#  endif
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h> 
# include "cub3d_bonus.h"

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strndup(char *str, size_t len);
bool	detect_n(char *buff);
char	*get_next_line(int fd);

#endif
