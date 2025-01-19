/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:58:36 by abennar           #+#    #+#             */
/*   Updated: 2025/01/19 10:22:29 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	is_wall(t_cub *cub, int x, int y)
{
	int	prev_grid_x;
	int	prev_grid_y;
	int	grid_x;
	int	grid_y;

	prev_grid_x = (int)floor(cub->pl.x / TILE_SIZE);
	prev_grid_y = (int)floor(cub->pl.y / TILE_SIZE);
	grid_x = (int)floor(x / TILE_SIZE);
	grid_y = (int)floor(y / TILE_SIZE);
	if (cub->map.map2d[grid_y][grid_x] == '1')
		return (true);
	if (grid_x != prev_grid_x && grid_y != prev_grid_y)
	{
		if (cub->map.map2d[grid_y][prev_grid_x] == '1'
			|| cub->map.map2d[prev_grid_y][grid_x] == '1')
			return (true);
	}
	return (false);
}

static void	update_player_pos(t_cub *cub, int x_steep, int y_steep)
{
	if (cub->pl.l_r == 1)
	{
		x_steep = -sin(cub->pl.rot_angle) * PLAYER_SPEED;
		y_steep = cos(cub->pl.rot_angle) * PLAYER_SPEED;
	}
	else if (cub->pl.l_r == -1)
	{
		x_steep = sin(cub->pl.rot_angle) * PLAYER_SPEED;
		y_steep = -cos(cub->pl.rot_angle) * PLAYER_SPEED;
	}
	if (cub->pl.u_d == 1)
	{
		x_steep = cos(cub->pl.rot_angle) * PLAYER_SPEED;
		y_steep = sin(cub->pl.rot_angle) * PLAYER_SPEED;
	}
	else if (cub->pl.u_d == -1)
	{
		x_steep = -cos(cub->pl.rot_angle) * PLAYER_SPEED;
		y_steep = -sin(cub->pl.rot_angle) * PLAYER_SPEED;
	}
	if (!is_wall(cub, cub->pl.x + x_steep, cub->pl.y + y_steep))
	{
		cub->pl.x += x_steep;
		cub->pl.y += y_steep;
	}
}

void	update(t_cub *cub)
{
	int	x_steep;
	int	y_steep;

	x_steep = 0;
	y_steep = 0;
	if (cub->pl.rot == -1)
	{
		cub->pl.rot_angle += ROT_SPEED;
		if (cub->pl.rot_angle > 2 * M_PI)
			cub->pl.rot_angle -= 2 * M_PI;
	}
	else if (cub->pl.rot == 1)
	{
		cub->pl.rot_angle -= ROT_SPEED;
		if (cub->pl.rot_angle < 0)
			cub->pl.rot_angle += 2 * M_PI;
	}
	update_player_pos(cub, x_steep, y_steep);
}
