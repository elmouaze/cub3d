/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:56:26 by abennar           #+#    #+#             */
/*   Updated: 2025/01/20 22:40:02 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DOOR_OPEN_DIST 2

int	wall_inter(t_cub *cub, double x, double y)
{
	long	xm;
	long	ym;
	char	cell;
	long	xp;
	long	yp;

	if (x < 0 || y < 0)
		return (1);
	xm = (long)(floor(x) / TILE_SIZE);
	ym = (long)(floor(y) / TILE_SIZE);
	if (xm < 0 || ym < 0 || xm >= cub->map.width || ym >= cub->map.height)
		return (1);
	cell = cub->map.map2d[ym][xm];
	if (cell == '1')
		return (1);
	if (cell == 'D')
	{
		xp = (long)(cub->pl.x / TILE_SIZE);
		yp = (long)(cub->pl.y / TILE_SIZE);
		if (labs(xm - xp) < DOOR_OPEN_DIST && labs(ym - yp) < DOOR_OPEN_DIST)
			return (false);
		return (2);
	}
	return (0);
}

void	wall_env(t_cub *cub, struct t_wall_data *data)
{
	float	hit_x;

	data->texture = get_texture(cub);
	data->dist_p = (S_W / 2.0f) / tan(FOV / 2.0f);
	data->wall_height = (TILE_SIZE / cub->ray.distance) * data->dist_p;
	data->wall_top = (S_H / 2) - ((int)data->wall_height / 2);
	data->wall_bottom = (S_H / 2) + ((int)data->wall_height / 2);
	data->wall_top = (int)fmax(data->wall_top, 0);
	data->wall_bottom = (int)fmin(data->wall_bottom, S_H);
	if (cub->ray.is_vertical)
	{
		hit_x = cub->ray.v_intery;
		hit_x -= floor(cub->ray.v_intery / TILE_SIZE) * TILE_SIZE;
	}
	else
	{
		hit_x = cub->ray.h_interx;
		hit_x -= floor(cub->ray.h_interx / TILE_SIZE) * TILE_SIZE;
	}
	data->x_offset = (hit_x / TILE_SIZE) * data->texture->width;
	data->x_offset = fmax(0, data->x_offset);
	data->distance_from_top = ((S_H / 2) - ((int)data->wall_height / 2));
}

void	set_direction(t_cub *cub)
{
	cub->is_door = false;
	cub->ray.ray_ngl = norm_angle(cub->ray.ray_ngl);
	cub->ray.up = (cub->ray.ray_ngl >= 0 && cub->ray.ray_ngl < M_PI);
	cub->ray.down = !cub->ray.up;
	cub->ray.left = cub->ray.ray_ngl > (M_PI / 2)
		&& cub->ray.ray_ngl < 3 * M_PI / 2;
	cub->ray.right = !cub->ray.left;
}

void	set_close_up_inter(t_cub *cub, float h_inter, float v_inter)
{
	if (h_inter < v_inter)
	{
		cub->ray.is_vertical = false;
		cub->ray.distance = h_inter;
	}
	else
	{
		cub->ray.is_vertical = true;
		cub->ray.distance = v_inter;
	}
}

void	cast_all_rays(t_cub *cub)
{
	int		i;
	float	h_inter;
	float	v_inter;
	int		v_door_hit;
	int		h_door_hit;

	i = 0;
	cub->ray.ray_ngl = (cub->pl.rot_angle - (FOV / 2));
	while (i < S_W)
	{
		set_direction(cub);
		h_inter = horizontal_caster(cub, cub->ray.ray_ngl, &h_door_hit);
		v_inter = vertical_caster(cub, cub->ray.ray_ngl, &v_door_hit);
		set_close_up_inter(cub, h_inter, v_inter);
		if (cub->ray.distance == h_inter)
			cub->is_door = h_door_hit == 2;
		else
			cub->is_door = v_door_hit == 2;
		cub->ray.distance *= cos(norm_angle(cub->ray.ray_ngl \
			- cub->pl.rot_angle));
		cub->ray.distance = fmax(cub->ray.distance, 0.1);
		render_walls(cub, i);
		cub->ray.ray_ngl += (FOV / S_W);
		i++;
	}
}
