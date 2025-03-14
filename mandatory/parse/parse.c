/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:28:55 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/24 09:31:01 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_type(char *str)
{
	int	size;

	size = ft_strlen(str);
	if (size < 4 || ft_strncmp(str + (size - 4), ".cub", 4) != 0)
		ft_perror("Error");
}

int	convert_rgb(char *color)
{
	char	**colors;
	int		red;
	int		green;
	int		blue;

	colors = ft_split(color, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
		return (-1);
	red = ft_atoi(colors[0]);
	green = ft_atoi(colors[1]);
	blue = ft_atoi(colors[2]);
	if (red < 0 || green < 0 || blue < 0)
		return (-1);
	return ((red << 16) | (green << 8) | blue);
}

int	check_line(char *tmp, t_data *map)
{
	if (ft_strncmp(tmp, "WE ", 2) == 0 && !map->we)
		return (map->we = ft_strtrim(tmp + 3, " \t"), 1);
	else if (ft_strncmp(tmp, "NO ", 2) == 0 && !map->we)
		return (map->no = ft_strtrim(tmp + 3, " \t"), 1);
	else if (ft_strncmp(tmp, "SO ", 2) == 0 && !map->so)
		return (map->so = ft_strtrim(tmp + 3, " \t"), 1);
	else if (ft_strncmp(tmp, "EA ", 2) == 0 && !map->ea)
		return (map->ea = ft_strtrim(tmp + 3, " \t"), 1);
	else if (ft_strncmp(tmp, "C ", 1) == 0)
		return (map->ciel_rgb = convert_rgb(tmp + 2), 1);
	else if (ft_strncmp(tmp, "F ", 1) == 0)
		return (map->floor_rgb = convert_rgb(tmp + 2), 1);
	return (0);
}

int	wall_check(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] && (line[i] == '1' || line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '\n')
		return (1);
	return (0);
}

void	parse_map(t_data *map, char *file)
{
	int		fd;
	int		cpt;
	char	*line;
	char	*tmp;

	(1) && (cpt = 0), (fd = open(file, O_RDONLY));
	if (fd < 0)
		return (ft_perror("open file failed"));
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strtrim(line, "\t \n");
		if (tmp && ft_strlen(tmp) > 0)
		{
			if (check_line(tmp, map) == 1)
				cpt++;
			else
				break ;
		}
		line = get_next_line(fd);
	}
	if (cpt != 6 || map->ciel_rgb < 0 || map->floor_rgb < 0 || wall_check(line))
		return (close(fd), ft_perror("Error"));
	fill_map(line, fd, map);
}
