/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:18:20 by abennar           #+#    #+#             */
/*   Updated: 2025/01/13 23:56:49 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	horizontal_caster(t_cub *cub, float angle, int *wall_hit)
{
	float	x_step;
	float	y_step;
	int		pxl;

	pxl = 0;
	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	cub->ray.h_intery = floor(cub->pl.y / TILE_SIZE) * TILE_SIZE;
	if (cub->ray.up) 
		cub->ray.h_intery += TILE_SIZE;
	else
	{
		y_step *= -1;
		pxl = -1;
	}
	cub->ray.h_interx = cub->pl.x + (cub->ray.h_intery - cub->pl.y) / tan(angle);
	if ((x_step > 0 && cub->ray.left) || (x_step < 0 && cub->ray.right))
			x_step *= -1;
	while (1)
	{
		*wall_hit = wall_inter(cub, cub->ray.h_interx, cub->ray.h_intery + pxl);
		if (*wall_hit)
			break;
		cub->ray.h_interx += x_step;
		cub->ray.h_intery += y_step;
	}
	return (sqrt(pow(cub->ray.h_interx - cub->pl.x, 2) + pow(cub->ray.h_intery
				- cub->pl.y, 2)));
}
