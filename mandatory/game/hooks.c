/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:58:36 by abennar           #+#    #+#             */
/*   Updated: 2024/11/20 11:01:34 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool is_wall(t_cub *cub, int x, int y)
{
    int prev_grid_x = (int)floor(cub->pl.x / SQR_SIZE);
    int prev_grid_y = (int)floor(cub->pl.y / SQR_SIZE);

    int grid_x = (int)floor(x / SQR_SIZE);
    int grid_y = (int)floor(y / SQR_SIZE);

    if (cub->map.map2d[grid_y][grid_x] == '1')
        return true;

    if (grid_x != prev_grid_x && grid_y != prev_grid_y)
        if (cub->map.map2d[grid_y][prev_grid_x] == '1' || cub->map.map2d[prev_grid_y][grid_x] == '1') 
            return true;

    return false;
}


void	update_player_pos(t_cub *cub, int x_steep , int y_steep)
{
	if (!is_wall(cub , cub->pl.x + x_steep, cub->pl.y + y_steep))
	{
		cub->pl.x += x_steep;
		cub->pl.y += y_steep;
	}
}

void	update(t_cub *cub)
{
	int x_steep = 0 ;
	int y_steep = 0;
	

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
	
	// Rendring frawmes



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
	// move_player(cub, x_steep, y_steep);
	update_player_pos(cub, x_steep , y_steep);
}