/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:28:55 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/10 04:03:23 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_file_type(char *str)
{
    int size;

    size = ft_strlen(str);
    if (size < 4 || ft_strncmp(str + (size - 4),".cub",4) != 0)
        ft_perror("Error");
}

int convert_rgb(char *color)
{
    char **colors;
    int red;
    int green;
    int blue;

    colors = ft_split(color, ',');
    if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
        return (-1);
    red = ft_atoi(colors[0]);
    green =  ft_atoi(colors[1]);
    blue =  ft_atoi(colors[2]);
    if (red < 0 || green < 0 || blue < 0)
        return (-1);
    return ((red << 16) | (green << 8) | blue);
 }

int check_line(char *tmp, t_data *map)
{
    if (ft_strncmp(tmp, "WE ", 2) == 0 && !map->WE) 
        return (map->WE = ft_strtrim(tmp + 3," \t"),1);
    else  if (ft_strncmp(tmp, "NO ", 2) == 0 && !map->NO)
        return (map->NO = ft_strtrim(tmp + 3," \t"), 1);
    else  if (ft_strncmp(tmp, "SO ", 2) == 0 && !map->SO)
        return (map->SO = ft_strtrim(tmp + 3," \t"), 1);
    else  if (ft_strncmp(tmp, "EA ", 2) == 0 && !map->EA)
        return (map->EA = ft_strtrim(tmp + 3," \t"), 1);
    else  if (ft_strncmp(tmp, "C ", 1) == 0)
        return (map->ciel_rgb = convert_rgb(tmp + 2),1);
    else  if (ft_strncmp(tmp, "F ",1) == 0)
        return (map->floor_color = convert_rgb(tmp + 2),1);
    
    return (0);
}

int wall_check(char *line)
{
    int i;

    i = 0;
    if (!line)
        return 1;
    while(line[i] && (line[i] == '1' || line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i] != '\n')
        return (1);
    return (0);
}
void parse_map(t_data *map, char *file)
{
    int fd,cpt = 0;
    char *line, *tmp;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (ft_perror("open file failed"));
    while ((line = get_next_line(fd)))
    {
        tmp = ft_strtrim(line,"\t \n");
        if (tmp && ft_strlen(tmp) > 0)
        {
            if (check_line(tmp,map) == 1)
                cpt++;
            else 
                break;
        }
        line = NULL;
    }
    if (cpt != 6 || map->ciel_rgb < 0 || map->floor_color < 0 || wall_check(line))
        return(close(fd), ft_perror("Error")); 
    fill_map(line, fd,map);
}

void init_map(t_data *map)
{
    map->map_hieght = -1;
    map->map_width = -1;
    map->x_player = -1;
    map->y_player = -1;
    map->ciel_rgb = -1; 
    map->floor_color = -1; 
    map->EA = NULL;
    map->NO = NULL;
    map->SO = NULL;
    map->WE = NULL;
}

void ft_perror(char *str)
{
    printf("%s\n",str);
    alloc(0,0);
    exit(1);
}
