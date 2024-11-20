/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:09:31 by ael-moua          #+#    #+#             */
/*   Updated: 2024/11/20 04:41:29 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*ft_fill(char *str)
{
	int		index;
	char	*res;

	index = 0;
	if (!str)
		return (NULL);
	res = alloc (1,ft_strlen(str) + 1);
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
        free(line);
        alloc(0,0);
    }
    res->line = ft_fill(line);
    free(line);
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
    if (c != '0' && c != '1' && c != ' ')
        return (ft_perror("Error"), 1);
    return (0);
}
void player_handler(int x, int y , t_data *data)
{
    if (data->x_player != -1)
        ft_perror("Error");
    data->x_player = x;
    data->y_player = y;

}
void check_map(char **map,t_data *data)
{
    int i;
    int j;
    int player;
    i = 0;
   
    while(map[i])   
    {
        j = 0;
        while (map[i][j])
        {
            player = is_player(map[i][j]);
            if (player)
                player_handler(i , j,data);
            if ((map[i][j] == '0' || player) && 
                (j == 0 || map[i][j - 1] == ' '))// left
                ft_perror("Error");
            else if ((map[i][j] == '0' || player) && 
                (map[i][j + 1] == 0 || map[i][j + 1] == ' '))// right
                 ft_perror("Error");
            else if ((map[i][j] == '0' || player) && 
                (i == 0 || map[i - 1][j] == ' '|| map[i - 1][j] == 0 )) //up
                 ft_perror("Error");
            else if ((map[i][j] == '0' || player) && 
                (!map[i + 1] || map[i + 1][j] == ' ' || map[i + 1][j] == 0))//down
                 ft_perror("Error");
            j++;
        }
        i++;
    }
    if (data->x_player == -1)
        ft_perror("Error");
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
        {
            free(line);
            break;
        }
        len = ft_strlen(line);
        add_token(&map,new_node(line,len));
        (len > width) && (width = len);
        line = NULL;
        height++;
    }
    while ((line = get_next_line(fd)))
    {
        if (check_end(line))
        {
            (1) && (free(line), close(fd));
            ft_perror("Error");
        }
        (1) && (free(line), line = NULL);
    }
    close(fd);
    build_map(map, height, width,data);
}
