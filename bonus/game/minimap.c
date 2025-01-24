/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:35:15 by abennar           #+#    #+#             */
/*   Updated: 2025/01/17 14:36:52 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_2d_tile(t_cub *cub, int x, int y, uint32_t color)
{
	int	dx;
	int	dy;
	int	size;

	dx = 0;
	size = MINIMAPS;
	while (dx < size)
	{
		dy = 0;
		while (dy < size)
		{
			mlx_put_pixel(cub->img, x + dx, y + dy, color);
			dy++;
		}
		dx++;
	}
}

static void	minimap_colomn(t_cub *cub, int plx, int ply, int gridy)
{
	int	x;
	int	y;
	int	gridx;

	gridx = plx - MINI_TILE;
	while (++gridx < plx + MINI_TILE)
	{
		x = (gridx - plx + MINI_TILE) * MINIMAPS;
		y = (gridy - ply + MINI_TILE) * MINIMAPS;
		if (gridx < 0 || gridy < 0 || gridx >= cub->map.width
			|| gridy >= cub->map.height)
		{
			draw_2d_tile(cub, x, y, BLACK);
			continue ;
		}
		if (cub->map.map2d[gridy][gridx] == '1')
			draw_2d_tile(cub, x, y, GREEN);
		else if (gridx == plx && gridy == ply)
			draw_2d_tile(cub, x, y, MAGENTA);
		else if (cub->map.map2d[gridy][gridx] == 'D')
			draw_2d_tile(cub, x, y, YELLOW);
		else
			draw_2d_tile(cub, x, y, BLACK);
	}
}

void	minimap(t_cub *cub)
{
	int			gridy;
	const int	plx = cub->pl.x / TILE_SIZE;
	const int	ply = cub->pl.y / TILE_SIZE;

	gridy = ply - MINI_TILE;
	while (++gridy < ply + MINI_TILE)
	{
		minimap_colomn(cub, plx, ply, gridy);
	}
}
