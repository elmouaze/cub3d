/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:29:20 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/17 11:01:20 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include <unistd.h>

typedef struct s_map 
{
    char            *line;
    struct s_map    *next;
}   t_map;

typedef struct s_data
{
    char   **map;
    int    map_hieght;
    int    map_width;
    int    x_player;
    int    y_player;
    char    *WE;
    char    *NO;
    char    *SO;
    char    *EA;

    int     ciel_rgb ; //ciel color 
    int     floor_color; 
} t_data;


int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void ft_perror(char *str);
char	*ft_strtrim(char *s1, char const *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
void ft_free_memory(char **res);
int	ft_atoi(const char *str);
char  **fill_map(char *str, int fd);
#endif