/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:36:45 by abennar           #+#    #+#             */
/*   Updated: 2024/11/20 14:09:34 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_line(t_cub *cub, int x, int y, int end_x, int end_y)
{
	int dx = abs(end_x - x);
	int dy = abs(end_y - y);
	int sx = (x < end_x) ? 1 : -1;
	int sy = (y < end_y) ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

    while (1)
    {
		// if (y < 0 || x < 0 || y > MAP || x > MAP_W)
		// 	break;

		mlx_put_pixel(cub->img, x, y, BLUE);
		if (x == end_x && y == end_y)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y += sy;
		}
	}
}


// void draw_the_player(t_cub *cub, int y, int x)
// {
// 		double d;
// 		d = sqrt(((x - cub->pl.x) ) * (x - (cub->pl.x ))
// 		+ (y - (cub->pl.y )) * (y - (cub->pl.y )));
// 		if (d  < 1)
// 			mlx_put_pixel(cub->img, x , y, GREEN);
// }

void draw(t_cub *cub)
{
	cast_all_rays(cub);
}

void game_loop(void *param)
{
	t_cub *cub = (t_cub *)param;
	mlx_delete_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, S_W, S_H);
	draw(cub);
	animation(cub);
	minimap(cub);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	update(cub);
}

void key_handler(mlx_key_data_t key_data, void *param)
{
	t_cub *cub;

	cub = param;
	// mlx_key_data_t key_data = cub->key;
	// if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
	// 		|| keydata.action == MLX_REPEAT))

	if (key_data.key == MLX_KEY_SPACE && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		cub->pl_action = true;
	if (key_data.key == MLX_KEY_W && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		cub->pl.u_d = 1;
	else if (key_data.key == MLX_KEY_S && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		cub->pl.u_d = -1;
	else if (key_data.key == MLX_KEY_A && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		cub->pl.l_r = -1;
	else if (key_data.key == MLX_KEY_D && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		cub->pl.l_r = 1;
	else if (key_data.key == MLX_KEY_LEFT && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		cub->pl.rot = 1;
	else if (key_data.key == MLX_KEY_RIGHT && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		cub->pl.rot = -1;
	// ft_reles(keydata, mlx);

	////////////////////
	///// key release //
	////////////////////

	if (key_data.key == MLX_KEY_D && (key_data.action == MLX_RELEASE))
		cub->pl.l_r = 0;
	else if (key_data.key == MLX_KEY_A && (key_data.action == MLX_RELEASE))
		cub->pl.l_r = 0;
	else if (key_data.key == MLX_KEY_S && (key_data.action == MLX_RELEASE))
		cub->pl.u_d = 0;
	else if (key_data.key == MLX_KEY_W && (key_data.action == MLX_RELEASE))
		cub->pl.u_d = 0;
	else if (key_data.key == MLX_KEY_LEFT && key_data.action == MLX_RELEASE)
		cub->pl.rot = 0;
	else if (key_data.key == MLX_KEY_RIGHT && key_data.action == MLX_RELEASE)
		cub->pl.rot = 0;
	// else if (key_data.key == MLX_KEY_SPACE && key_data.action == MLX_RELEASE)
	// 	cub->pl_action = false;
}

void draw_2d_tile(t_cub *cub, int x, int y, int size, uint32_t color)
{
    int dx = 0;
	int dy;
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

void minimap(t_cub *cub)
{
    int plx = cub->pl.x / SQR_SIZE; 
    int ply = cub->pl.y / SQR_SIZE;

    int gridy = ply - MINI_TILE;
    int gridx;
    int x, y;

    while (++gridy < ply + MINI_TILE)
    {
        gridx = plx - MINI_TILE;
        while (++gridx < plx + MINI_TILE)
        {
            x = (gridx - plx + MINI_TILE) * MINIMAPS;
            y = (gridy - ply + MINI_TILE) * MINIMAPS;
            if (gridx < 0 || gridy < 0 || gridx >= cub->map.width || gridy >= cub->map.height)
            {
                draw_2d_tile(cub, x, y, MINIMAPS, BLACK);
                continue;
            }
            if (cub->map.map2d[gridy][gridx] == '1')
                draw_2d_tile(cub, x, y, MINIMAPS, GREEN);
            else if (gridx == plx && gridy == ply)
                draw_2d_tile(cub, x, y, MINIMAPS, MAGENTA);
            else if (cub->map.map2d[gridy][gridx] == 'D')
                draw_2d_tile(cub, x, y, MINIMAPS, YELLOW);
            else
                draw_2d_tile(cub, x, y, MINIMAPS, BLACK);
        }
    }
}

void start_the_game(t_cub *cub)
{
	mlx_set_mouse_pos(cub->mlx, S_W / 2, S_H / 2);
	mlx_loop_hook(cub->mlx, &game_loop, cub);
	mlx_key_hook(cub->mlx, &key_handler, cub);
	mlx_mouse_hook(cub->mlx, &mouse_handler, cub);
	mlx_cursor_hook(cub->mlx, &cursor_handler, cub);
}