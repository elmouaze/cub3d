/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:36:45 by abennar           #+#    #+#             */
/*   Updated: 2025/01/14 04:03:48 by abennar          ###   ########.fr       */
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

void game_loop(void *param)
{
	t_cub *cub = (t_cub *)param;
	mlx_delete_image(cub->mlx, cub->img);
	cub->img = NULL;
	cub->img = mlx_new_image(cub->mlx, S_W, S_H);
	if (!cub->img)
	{
		ft_perror("Can't creat mlx-image");
		mlx_close_window(cub->mlx);
		free_exit(1, cub);
	}
	cast_all_rays(cub);
	animation(cub);
	minimap(cub);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
	{
		ft_perror("mlx Failed");
		mlx_delete_image(cub->mlx, cub->img);
		mlx_close_window(cub->mlx);
		free_exit(1, cub);
	}
	update(cub);
}

void key_handler(mlx_key_data_t key_data, void *param)
{
	t_cub *cub;

	cub = param;
	// mlx_key_data_t key_data = cub->key;
	// if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
	// 		|| keydata.action == MLX_REPEAT))

	if (key_data.key == MLX_KEY_ESCAPE && (key_data.action == MLX_PRESS))
	{
		mlx_delete_image(cub->mlx, cub->img);
		mlx_close_window(cub->mlx);
		free_exit(0, cub);
	}


	if (key_data.key == MLX_KEY_SPACE && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT) && cub->pl_action == false)
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
    int plx = cub->pl.x / TILE_SIZE; 
    int ply = cub->pl.y / TILE_SIZE;

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
	cub->mlx = mlx_init(S_W, S_H, "cub3d", 0);
	if (!cub->mlx)
	{
		ft_perror("Failed to connect to mlx");
		free_exit(1, cub);
	}
	mlx_set_mouse_pos(cub->mlx, S_W / 2, S_H / 2);
	mlx_loop_hook(cub->mlx, &game_loop, cub);
	mlx_key_hook(cub->mlx, &key_handler, cub);
	mlx_mouse_hook(cub->mlx, &mouse_handler, cub);
	mlx_cursor_hook(cub->mlx, &cursor_handler, cub);
	mlx_close_hook(cub->mlx, &close_func, cub);
	mlx_loop(cub->mlx);
}