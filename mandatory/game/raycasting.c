/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:56:26 by abennar           #+#    #+#             */
/*   Updated: 2025/01/14 01:53:45 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define DOOR_OPEN_DIST 2

double		norm_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int wall_inter(t_cub *cub, double x, double y)
{
    if (x < 0 || y < 0)
        return 1;

    long xm = (long)(floor(x) / TILE_SIZE);
    long ym = (long)(floor(y) / TILE_SIZE);

    if (xm < 0 || ym < 0 || xm >= cub->map.width || ym >= cub->map.height)
        return 1;
    char cell = cub->map.map2d[ym][xm];

    if (cell == '1')
        return 1;

    if (cell == 'D') {
        long xp = (long)(cub->pl.x / TILE_SIZE);
        long yp = (long)(cub->pl.y / TILE_SIZE);

        if (labs(xm - xp) < DOOR_OPEN_DIST && labs(ym - yp) < DOOR_OPEN_DIST)
            return false;
        return 2;
    }
    return 0;
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

uint32_t    get_texture_color(mlx_texture_t	*tex, int x, int y)
{
    unsigned char *pixels = tex->pixels;
    int index = (y * tex->width + x) * 4; 
    return (pixels[index + 3] << 24) | (pixels[index + 0] << 16) | (pixels[index + 1] << 8) | (pixels[index + 2]);
}

void	render_walls(t_cub *cub, int x)
{
	mlx_texture_t	*texture;

	texture = get_texture(cub);
    int dist_p = (S_W / 2.0f) / tan(FOV / 2.0f);
    int wall_height = (TILE_SIZE / cub->ray.distance) * dist_p;
    int wall_top = (S_H / 2) - ((int)wall_height / 2);
    int wall_bottom = (S_H / 2) + ((int)wall_height / 2);

	wall_top = (int)fmax(wall_top, 0);
	wall_bottom = (int)fmin(wall_bottom, S_H);

    float hit_x;
    if (cub->ray.is_vertical)
        hit_x = cub->ray.v_intery - floor(cub->ray.v_intery / TILE_SIZE) * TILE_SIZE;
    else
        hit_x = cub->ray.h_interx - floor(cub->ray.h_interx / TILE_SIZE) * TILE_SIZE;

    float x_offset = (hit_x / TILE_SIZE) * texture->width;
    x_offset = fmax(0, x_offset);
	float distance_from_top = ((S_H / 2) - ((int)wall_height / 2));

	int i = 0;
	while (i < wall_top)
        mlx_put_pixel(cub->img, x, i++, cub->ceilling_color);
    while (wall_top < wall_bottom)
    {
        float normalized_y = (wall_top - distance_from_top) / wall_height;
        float y_offset = normalized_y * texture->height;
        y_offset = fmax(0, y_offset);
        unsigned int color = get_texture_color(texture, (int)x_offset, (int)y_offset);
        mlx_put_pixel(cub->img, x, wall_top++, color);
    }
	i = wall_bottom;
	while (i < S_H)
        mlx_put_pixel(cub->img, x, i++, cub->floor_color);
}

void	cast_all_rays(t_cub *cub)
{
	int i = 0;
	float  h_inter;
	float  v_inter;
	int		v_door_hit;
	int		h_door_hit;


	cub->ray.ray_ngl =  (cub->pl.rot_angle - ( FOV / 2));
	while (i < S_W)
	{
		cub->is_door = false;
		cub->ray.ray_ngl = norm_angle(cub->ray.ray_ngl);
		cub->ray.up = (cub->ray.ray_ngl >= 0 && cub->ray.ray_ngl < M_PI);
		cub->ray.down = !cub->ray.up;
		cub->ray.left = cub->ray.ray_ngl > M_PI / 2 && cub->ray.ray_ngl < 3 * M_PI / 2;
		cub->ray.right = !cub->ray.left;
		h_inter = horizontal_caster(cub,  cub->ray.ray_ngl, &h_door_hit);
		v_inter = vertical_caster(cub,  cub->ray.ray_ngl, &v_door_hit); 
		
		if (h_inter < v_inter)
		{
  			 cub->ray.distance = h_inter;
			 cub->ray.is_vertical = false;
			cub->is_door = h_door_hit == 2;
		}
		else
		{
			cub->ray.distance = v_inter;
			cub->ray.is_vertical = true; 
			cub->is_door = v_door_hit == 2;
		}
		cub->ray.distance *= cos(norm_angle(cub->ray.ray_ngl - cub->pl.rot_angle));
		if (cub->ray.distance < 0.1f)
			cub->ray.distance = 0.1f;
		render_walls(cub, i);

		cub->ray.ray_ngl += (FOV / S_W);
		i++;
	}
}


