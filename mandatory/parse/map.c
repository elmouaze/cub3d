/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:09:31 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/24 09:38:17 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_handler(int x, int y, t_data *data)
{
	if (data->x_player != -1)
		ft_perror("Error: Just one player is allowed");
	data->x_player = y;
	data->y_player = x;
}

void	map_error(char **map, int i, int j)
{
	if ((map[i][j] == '0' || map[i][j] == 'D'))
	{
		if (j == 0 || map[i][j - 1] == ' ')
			ft_perror("Error: Unclosed map");
		else if (map[i][j + 1] == 0 || map[i][j + 1] == ' ')
			ft_perror("Error: Unclosed map");
		else if (i == 0 || map[i - 1][j] == ' ' || map[i - 1][j] == 0)
			ft_perror("Error: Unclosed map");
		else if (!map[i + 1] || map[i + 1][j] == ' ' || map[i + 1][j] == 0)
			ft_perror("Error: Unclosed map");
	}
	if (map[i][j] == 'D')
	{
		if (map[i][j - 1] == 'D' || map[i][j + 1] == 'D'
		|| map[i + 1][j] == 'D' || map[i - 1][j] == 'D')
			ft_perror("Error: Multiple Doors near each other ");
		if (((map[i][j - 1] == '1') + (map[i][j + 1] == '1') != 2)
			&& ((map[i + 1][j] == '1') + (map[i - 1][j] == '1') != 2))
			ft_perror("Error: A door without a wall");
	}
}

void	check_map(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
			{
				player_handler(i, j, data);
				data->pl_cell = map[i][j];
				map[i][j] = '0';
			}
			map_error(map, i, j);
			j++;
		}
		i++;
	}
	if (data->x_player == -1)
		ft_perror("Error: No player");
	data->map = map;
}

void	build_map(t_parse_map *map, int size, size_t width, t_data *data)
{
	char	**res;
	int		i;
	size_t	j;

	i = 0;
	res = (char **) alloc (1, sizeof(char *) * (size + 1));
	if (!res)
		alloc(0, 0);
	while (map)
	{
		j = map->size;
		res[i] = ft_calloc(width, 1);
		ft_strlcpy(res[i], map->line, map->size);
		map = map->next;
		i++;
	}
	res[i] = NULL;
	data->map_hieght = size;
	data->map_width = width;
	check_map(res, data);
}

void	fill_map(char *str, int fd, t_data *data)
{
	t_parse_map	*map;
	int			height;
	char		*line;
	size_t		width;
	size_t		len;

	(1) && (map = NULL), (line = NULL), (len = ft_strlen(str));
	(1) && (height = 1), (width = 0), (line = get_next_line(fd));
	add_token(&map, new_node(str, len));
	while (line)
	{
		if (!check_end(line))
			break ;
		len = ft_strlen(line);
		add_token(&map, new_node(line, len));
		(len > width) && (width = len);
		(1) && (height++), (line = get_next_line(fd));
	}
	while (line)
	{
		if (check_end(line))
			(1) && close(fd), ft_perror("Error");
		line = get_next_line(fd);
	}
	(1) && (close(fd)), (build_map(map, height, width, data));
}
