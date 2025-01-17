/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:09:31 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/17 12:01:48 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_fill(char *str)
{
	int		index;
	char	*res;

	index = 0;
	if (!str)
		return (NULL);
	res = alloc (1, ft_strlen(str) + 1);
	if (!res)
		return (alloc(0,0), NULL);
	while (str[index] != '\0')
	{
		res[index] = str[index];
		index++;
	}
	res[index] = '\0';
	return (res);
}

static t_map    *new_node(char *line,size_t len)
{
	t_map	*res;

	res = alloc(1,sizeof(t_map));
    if(!res)
    {
        alloc(0,0);
    }
    res->line = ft_fill(line);
    res->size = len;
    res->next = NULL;
	return (res);
}

static void	add_token(t_map **lst, t_map *new)
{
	t_map	*node;

	if (!*lst)
		*lst = new;
	else
	{
		node = *lst;
		while (node && (node)->next != NULL)
			node = (node)->next;
		(node)->next = new;
	}
}

int check_end(char *line)
{
    int i;

    i = 0;
    while(line[i] && (line[i] == ' ' || line[i] == '\n'))
        i++;
    if (!line[i])
        return(0);
    return (1);
}

int is_player(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
    if (c != '0' && c != '1' && c != ' ' && c != 'D')
        return (ft_perror("Error: Forbidden symbols"), 1);
    return (0);
}
void player_handler(int x, int y , t_data *data)
{
    if (data->x_player != -1)
        ft_perror("Error: Just one player is allowed");
    data->x_player = y;
    data->y_player = x;
}

void map_error(char **map , int i , int j)
{    
    if ((map[i][j] == '0' || map[i][j] == 'D'))
    {
        if(j == 0 || map[i][j - 1] == ' ')// left
            ft_perror("Error: Unclosed map");
        else if (map[i][j + 1] == 0 || map[i][j + 1] == ' ')// right
            ft_perror("Error: Unclosed map");
        else if (i == 0 || map[i - 1][j] == ' '|| map[i - 1][j] == 0 ) //up
            ft_perror("Error: Unclosed map");
        else if (!map[i + 1] || map[i + 1][j] == ' ' || map[i + 1][j] == 0)//down
            ft_perror("Error: Unclosed map");
    }
    if (map[i][j] == 'D') 
    {
        if (map[i][j - 1] == 'D' || map[i][j + 1] == 'D'
        || map[i + 1][j] == 'D' || map[i - 1][j] == 'D')
            ft_perror("Error: Multiple Doors near each other ");
         if (((map[i][j - 1] == '1') + (map[i][j + 1] == '1')
          + (map[i + 1][j] == '1') + (map[i - 1][j] == '1')) < 2)
            ft_perror("Error: A door without a wall");
    }
}

void check_map(char **map,t_data *data)
{
    int i;
    int j;
    i = 0;
   
    while(map[i])   
    {
        j = 0;
        while (map[i][j])
        {
            if (is_player(map[i][j]))
			{
                player_handler(i , j,data);
                data->pl_cell = map[i][j];
				map[i][j] = '0';
			}
            map_error(map, i , j);
            j++;
        }
        i++;
    }
    if (data->x_player == -1)
        ft_perror("Error: No player");
    data->map = map;
}

void build_map(t_map *map, int size,size_t width,t_data *data)
{
    char **res;
    int i = 0;
    size_t j;

    if (!(res = (char **) alloc (1,sizeof(char *) * (size + 1))))
        alloc(0,0);
    while (map)
    {
        j = map->size;
        res[i] = ft_calloc(width,1);
        ft_strlcpy(res[i], map->line, map->size);
        map = map->next;
        i++;
    }
    res[i] = NULL;
    data->map_hieght = size;
    data->map_width = width;
    check_map(res,data);
}

void fill_map(char *str, int fd,t_data *data)
{
    t_map   *map;
    int     height;
    char    *line;
    size_t width, len;

    (1) &&  (map = NULL), (line = NULL), (len = ft_strlen(str));
    height = 1;
    width = 0;
    add_token(&map,new_node(str, len));
    while ((line = get_next_line(fd)))
    {
        if (!check_end(line))
            break;
        len = ft_strlen(line);
        add_token(&map,new_node(line,len));
        (len > width) && (width = len);
        line = NULL;
        height++;
    }
    while ((line = get_next_line(fd)))
    {
        if (check_end(line))
            (1) && close(fd),ft_perror("Error");
        line = NULL;
    }
    close(fd);
    build_map(map, height, width,data);
}
