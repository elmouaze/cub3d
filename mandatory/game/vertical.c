/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:18:34 by abennar           #+#    #+#             */
/*   Updated: 2024/11/20 11:01:43 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	vertical_caster(t_cub *cub, float angle, int *wall_hit)
{
	float	x_step;
	float	y_step;
	int		pxl;

	pxl = 0;
	x_step = SQR_SIZE;
	y_step = x_step * tan(angle);
	cub->ray.v_interx = floor(cub->pl.x / SQR_SIZE) * SQR_SIZE;
	if (cub->ray.right)
		cub->ray.v_interx += SQR_SIZE;
	else
	{
		x_step *= -1;
		pxl = -1;
	}
	cub->ray.v_intery =  cub->pl.y + tan(angle) * (cub->ray.v_interx - cub->pl.x);
	if ((y_step < 0 && cub->ray.up) || (y_step > 0 && cub->ray.down))
		y_step *= -1;
	while (1)
	{
		*wall_hit = wall_inter(cub, cub->ray.v_interx  + pxl, cub->ray.v_intery);
		if (*wall_hit)
			break;
		cub->ray.v_interx += x_step;
		cub->ray.v_intery += y_step;
	}
	return (sqrt(pow(cub->ray.v_interx - cub->pl.x, 2) + pow(cub->ray.v_intery
				- cub->pl.y, 2)));
}

