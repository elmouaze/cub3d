/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:28:55 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/17 11:02:59 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void check_file_type(char *str)
{
    int size;

    size = ft_strlen(str);
    if (size < 4 || ft_strncmp(str + (size - 4),".cub",4) != 0)
        ft_perror("a map should be in *.cub format ");
}

int check_texture(char *file)
{
    int size;

    size = ft_strlen(file);
    if (size < 4 || ft_strncmp(file + (size - 4),".xpm",4) != 0)
        return (0);
    return (1);
}
int convert_rgb(char *color)
{
    char **colors;
    int red,green,blue;

    colors = ft_split(color,',');
    if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
        return (ft_free_memory(colors), -1);
    red = ft_atoi(colors[0]);
    green =  ft_atoi(colors[1]);
    blue =  ft_atoi(colors[2]);
    if (red < 0 || green < 0 || blue < 0)
        return (ft_free_memory(colors), -1);
    ft_free_memory(colors);
    return ((red << 16) | (green << 8) | blue);
 }

int check_line(char *tmp, t_data *map)
{
    if (ft_strncmp(tmp, "WE ", 2) == 0 && !map->WE) 
        return (map->WE = ft_strtrim(tmp + 3," \t"),check_texture(map->WE));
    else  if (ft_strncmp(tmp, "NO ", 2) == 0 && !map->NO)
        return (map->NO = ft_strtrim(tmp + 3," \t"),check_texture(map->NO));
    else  if (ft_strncmp(tmp, "SO ", 2) == 0 && !map->SO)
        return (map->SO = ft_strtrim(tmp + 3," \t"),check_texture(map->SO));
    else  if (ft_strncmp(tmp, "EA ", 2) == 0 && !map->EA)
        return (map->EA = ft_strtrim(tmp + 3," \t"),check_texture(map->EA));
    else  if (ft_strncmp(tmp, "C ", 1) == 0)
        return (map->ciel_rgb = convert_rgb(tmp + 2));
    else  if (ft_strncmp(tmp, "F ",1) == 0)
        return (map->floor_color = convert_rgb(tmp + 2));
    return (0);
}

int wall_check(char *line)
{
    int i;

    i = 0;
    while(line[i] && (line[i] == '1' || line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i] != '\n')
        return (printf("%c\n",line[i]),1);
    return (0);
}
void parse_map(t_data *map, char *file)
{
    int fd,cpt = 0;
    char *line, *tmp;
    (void)map;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (ft_perror("open file failed"));
    while ((line = get_next_line(fd)))
    {
        tmp = ft_strtrim(line,"\t \n");
        if (tmp && ft_strlen(tmp) > 0)
        {
            if (check_line(tmp,map))
                cpt++;
            else 
            {
                free(tmp);
                break;
            }
        }
        free(tmp);
        free(line);
    }
    if (cpt != 6 || map->ciel_rgb < 0 || map->floor_color < 0 || wall_check(line))
        return(ft_perror("Map problem"), close(fd), free(line)); // free textures
    if (!(map->map = fill_map(line, fd)))
        return ;//error
}

void init_map(t_data *map)
{
    map->map_hieght = -1;
    map->map_width = -1;
    map->x_player = -1;
    map->y_player = -1;
    map->ciel_rgb = -1; 
    map->floor_color = -1; 
}

void ft_perror(char *str)
{
    printf("%s\n",str);
    exit(1);
}

void print_data(t_data *data)
{
    // Check if data is NULL
    if (!data) {
        printf("Data is NULL.\n");
        return;
    }
    // Print textures (if they exist)
    printf("Textures:\n");
    printf("  West: %s\n", data->WE ? data->WE : "NULL");
    printf("  North: %s\n", data->NO ? data->NO : "NULL");
    printf("  South: %s\n", data->SO ? data->SO : "NULL");
    printf("  East: %s\n", data->EA ? data->EA : "NULL");

    // Print color values (in decimal)
    printf("Sky color (Ciel): %d\n", data->ciel_rgb);
    printf("Floor color: %d\n", data->floor_color);
}

int main(int ac, char **av)
{
    t_data   map;

    (void)map;
    if (ac != 2)
        ft_perror("invalide arguments");
    check_file_type(av[1]);
    init_map(&map);
    parse_map(&map, av[1]);
    print_data(&map);
}
