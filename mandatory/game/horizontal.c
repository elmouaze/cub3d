/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:18:20 by abennar           #+#    #+#             */
/*   Updated: 2025/01/17 15:03:11 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	go2_wall(t_cub *cub, int *wall_hit)
{
	while (1)
	{
		*wall_hit = wall_inter(cub, cub->ray.h_interx, \
			cub->ray.h_intery + cub->pxl);
		if (*wall_hit)
			break ;
		cub->ray.h_interx += cub->x_step;
		cub->ray.h_intery += cub->y_step;
	}
}

float	horizontal_caster(t_cub *cub, float angle, int *wall_hit)
{
	cub->pxl = 0;
	cub->y_step = TILE_SIZE;
	cub->x_step = TILE_SIZE / tan(angle);
	cub->ray.h_intery = floor(cub->pl.y / TILE_SIZE) * TILE_SIZE;
	if (cub->ray.up)
		cub->ray.h_intery += TILE_SIZE;
	else
	{
		cub->y_step *= -1;
		cub->pxl = -1;
	}
	cub->ray.h_interx = cub->pl.x + (cub->ray.h_intery - cub->pl.y) \
		/ tan(angle);
	if ((cub->x_step > 0 && cub->ray.left)
		|| (cub->x_step < 0 && cub->ray.right))
		cub->x_step *= -1;
	go2_wall(cub, wall_hit);
	return (sqrt(pow(cub->ray.h_interx - cub->pl.x, 2) + pow(cub->ray.h_intery
				- cub->pl.y, 2)));
}
