/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:29:35 by abennar           #+#    #+#             */
/*   Updated: 2025/01/25 11:08:08 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint32_t	get_rgba(uint32_t rgb)
{
	return ((rgb << 8) | 255);
}

void	trans_data(t_data *data, t_cub *cub)
{
	ft_memset(cub, 0, sizeof(t_cub));
	if (data->pl_cell == 'N')
		cub->pl.rot_angle = 4.71238898038;
	else if (data->pl_cell == 'S')
		cub->pl.rot_angle = 1.57079632679;
	else if (data->pl_cell == 'E')
		cub->pl.rot_angle = 0;
	else
		cub->pl.rot_angle = M_PI;
	cub->map.height = data->map_hieght;
	cub->map.width = data->map_width;
	cub->pl.x = data->x_player * TILE_SIZE;
	cub->pl.y = data->y_player * TILE_SIZE;
	cub->map.map2d = data->map;
	cub->textures[0] = mlx_load_png(data->no);
	cub->textures[1] = mlx_load_png(data->so);
	cub->textures[2] = mlx_load_png(data->we);
	cub->textures[3] = mlx_load_png(data->ea);
	cub->door = mlx_load_png("./textures/door.png");
	if (!cub->textures[0] || !cub->textures[1]
		|| !cub->textures[2] || !cub->textures[3])
		free_exit(1, cub);
	cub->ceilling_color = get_rgba(data->ciel_rgb);
	cub->floor_rgb = get_rgba(data->floor_rgb);
	cub->mouse = false;
}

void	import_sprites(t_cub *cub)
{
	int		i;
	char	*path;
	char	*png_path;

	i = 0;
	path = ft_strndup("./frames/", 9);
	while (i < FRAMES)
	{
		png_path = ft_strjoin(path, ft_strjoin(ft_itoa(i), ".png"));
		cub->anim[i] = mlx_load_png(png_path);
		if (!cub->anim[i])
			free_exit(1, cub);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_cub	cub;
	t_data	map;

	if (ac != 2)
		ft_perror("Error: Bad args");
	check_file_type(av[1]);
	init_map(&map);
	parse_map(&map, av[1]);
	trans_data(&map, &cub);
	import_sprites(&cub);
	start_the_game(&cub);
}
