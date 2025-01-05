/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:56:26 by abennar           #+#    #+#             */
/*   Updated: 2024/11/20 11:12:28 by ael-moua         ###   ########.fr       */
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

bool wall_inter(t_cub *cub, double x, double y)
{
    if (x < 0 || y < 0)
        return true;

    long xm = (long)(floor(x) / SQR_SIZE);
    long ym = (long)(floor(y) / SQR_SIZE);

    if (xm < 0 || ym < 0 || xm >= cub->map.width || ym >= cub->map.height)
        return true;
    char cell = cub->map.map2d[ym][xm];

    if (cell == '1')
        return true;

    if (cell == 'D') {
        long xp = (long)(cub->pl.x / SQR_SIZE);
        long yp = (long)(cub->pl.y / SQR_SIZE);

        if (labs(xm - xp) < DOOR_OPEN_DIST && labs(ym - yp) < DOOR_OPEN_DIST)
            return false;
        cub->is_door = true;
        return true;
    }
    return false;
}

mlx_texture_t	*get_texture(t_cub *cub)
{
	if (cub->is_door == true)
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

void	render_walls(t_cub *cub, int x) // TODO add prefix PART 1 part n
{
	mlx_texture_t	*texture;

	texture = get_texture(cub);
    float dist_p = (S_W / 2.0f) / tan(FOV / 2.0f);
    float wall_height = (SQR_SIZE / cub->ray.distance) * dist_p;
    int wall_top = (S_H / 2) - ((int)wall_height / 2);
    int wall_bottom = (S_H / 2) + ((int)wall_height / 2);

	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= S_H)
		wall_bottom = S_H;
    float hit_x;
    if (cub->ray.is_vertical)
        hit_x = cub->ray.v_intery - floor(cub->ray.v_intery / SQR_SIZE) * SQR_SIZE;
    else
        hit_x = cub->ray.h_interx - floor(cub->ray.h_interx / SQR_SIZE) * SQR_SIZE;
    float tex_x = (hit_x / SQR_SIZE) * texture->width;
    if (cub->ray.is_vertical && cub->ray.left)
        tex_x = texture->width - tex_x - 1;
    if (!cub->ray.is_vertical && cub->ray.up)
        tex_x = texture->width - tex_x - 1;
    tex_x = fmax(0, fmin(tex_x, texture->width - 1));
    int y = wall_top;
	float distance_from_top = ((S_H / 2) - ((int)wall_height / 2));

	int i = 0;
	while (i < y)
	{
        mlx_put_pixel(cub->img, x, i++, cub->ceilling_color);
		i++;
	}
    while (y < wall_bottom)
    {
        float normalized_y = (y - distance_from_top) / wall_height;
        float tex_y = normalized_y * texture->height;
        tex_y = fmax(0, fmin(tex_y, texture->height - 1));
        unsigned int color = get_texture_color(texture, (int)tex_x, (int)tex_y);
        mlx_put_pixel(cub->img, x, y++, color);
    }
	i = wall_bottom;
	while (i < S_H)
	{
        mlx_put_pixel(cub->img, x, i++, cub->floor_color);
		i++;
	}
}

void	cast_all_rays(t_cub *cub)
{
	int i = 0;
	float  h_inter;
	float  v_inter;


	cub->ray.ray_ngl =  (cub->pl.rot_angle - ( FOV / 2));
	while (i < S_W)
	{
		cub->is_door = false;
		cub->ray.ray_ngl = norm_angle(cub->ray.ray_ngl);
		cub->ray.up = (cub->ray.ray_ngl >= 0 && cub->ray.ray_ngl < M_PI);
		cub->ray.down = !cub->ray.up;
		cub->ray.left = cub->ray.ray_ngl > M_PI / 2 && cub->ray.ray_ngl < 3 * M_PI / 2;
		cub->ray.right = !cub->ray.left;
		h_inter = horizontal_caster(cub,  cub->ray.ray_ngl);
		v_inter = vertical_caster(cub,  cub->ray.ray_ngl); 
		
		if (h_inter < v_inter)
		{
  			 cub->ray.distance = h_inter;
			 cub->ray.is_vertical = false;
		}
		else
		{
		   cub->ray.distance = v_inter;
			cub->ray.is_vertical = true;
			 cub->is_door = false;
  
		}
		
		cub->ray.distance *= cos(norm_angle(cub->ray.ray_ngl - cub->pl.rot_angle));
		if (cub->ray.distance < 0.1f)
			cub->ray.distance = 0.1f;
		render_walls(cub, i);

		cub->ray.ray_ngl += (FOV / S_W);
		i++;
	}
}


