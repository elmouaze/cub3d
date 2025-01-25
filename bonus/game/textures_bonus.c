/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:52:01 by abennar           #+#    #+#             */
/*   Updated: 2025/01/25 11:08:08 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	norm_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

mlx_texture_t	*get_texture(t_cub *cub)
{
	if (cub->is_door)
		return (cub->door);
	if (cub->ray.is_vertical)
	{
		if (cub->ray.right)
			return (cub->textures[0]);
		else
			return (cub->textures[1]);
	}
	else
	{
		if (cub->ray.up)
			return (cub->textures[2]);
		else
			return (cub->textures[3]);
	}
}

static uint32_t	get_texture_color(mlx_texture_t	*tex, int x, int y)
{
	int				index;
	unsigned char	*pixels;

	pixels = tex->pixels;
	index = (y * tex->width + x) * 4;
	return ((pixels[index + 3] << 24) | (pixels[index + 0] << 16) \
	| (pixels[index + 1] << 8) | (pixels[index + 2]));
}

void	render_walls(t_cub *cub, int x)
{
	struct s_wall_data	data;
	int					i;
	float				y_offset;
	float				y;
	unsigned int		color;

	i = 0;
	wall_env(cub, &data);
	while (i < data.wall_top)
		mlx_put_pixel(cub->img, x, i++, cub->ceilling_color);
	while (data.wall_top < data.wall_bottom)
	{
		y = (data.wall_top - data.distance_from_top) / data.wall_height;
		y_offset = y * data.texture->height;
		y_offset = fmax(0, y_offset);
		color = get_texture_color(data.texture, data.x_offset, y_offset);
		mlx_put_pixel(cub->img, x, data.wall_top++, color);
	}
	i = data.wall_bottom;
	while (i < S_H)
		mlx_put_pixel(cub->img, x, i++, cub->floor_rgb);
}
