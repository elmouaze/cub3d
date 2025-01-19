/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:18:34 by abennar           #+#    #+#             */
/*   Updated: 2025/01/19 10:36:19 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	go2_wall(t_cub *cub, int *wall_hit)
{
	while (1)
	{
		*wall_hit = wall_inter(cub, cub->ray.v_interx \
			+ cub->pxl, cub->ray.v_intery);
		if (*wall_hit)
			break ;
		cub->ray.v_interx += cub->x_step;
		cub->ray.v_intery += cub->y_step;
	}
}

float	vertical_caster(t_cub *cub, float angle, int *wall_hit)
{
	cub->pxl = 0;
	cub->x_step = TILE_SIZE;
	cub->y_step = cub->x_step * tan(angle);
	cub->ray.v_interx = floor(cub->pl.x / TILE_SIZE) * TILE_SIZE;
	if (cub->ray.right)
		cub->ray.v_interx += TILE_SIZE;
	else
	{
		cub->x_step *= -1;
		cub->pxl = -1;
	}
	cub->ray.v_intery = cub->pl.y + tan(angle) \
		* (cub->ray.v_interx - cub->pl.x);
	if ((cub->y_step < 0 && cub->ray.up) || (cub->y_step > 0 && cub->ray.down))
		cub->y_step *= -1;
	go2_wall(cub, wall_hit);
	return (sqrt(pow(cub->ray.v_interx - cub->pl.x, 2) + pow(cub->ray.v_intery
				- cub->pl.y, 2)));
}
