/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:36:45 by abennar           #+#    #+#             */
/*   Updated: 2025/01/25 11:08:08 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// TODO bonus -> animation, minimap

static void	game_loop(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
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

static void	release_keys(mlx_key_data_t key_data, t_cub *cub)
{
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

#define PRESS 3

static void	key_handler(mlx_key_data_t key_data, void *param)
{
	t_cub	*cub;

	cub = param;
	if (key_data.key == MLX_KEY_ESCAPE && (key_data.action == MLX_PRESS))
	{
		mlx_delete_image(cub->mlx, cub->img);
		mlx_close_window(cub->mlx);
		free_exit(0, cub);
	}
	if (key_data.key == MLX_KEY_SPACE && ((key_data.action & PRESS) != 0))
		cub->pl_action = true;
	if (key_data.key == MLX_KEY_W && ((key_data.action & PRESS) != 0))
		cub->pl.u_d = 1;
	else if (key_data.key == MLX_KEY_S && ((key_data.action & PRESS) != 0))
		cub->pl.u_d = -1;
	else if (key_data.key == MLX_KEY_A && ((key_data.action & PRESS) != 0))
		cub->pl.l_r = -1;
	else if (key_data.key == MLX_KEY_D && ((key_data.action & PRESS) != 0))
		cub->pl.l_r = 1;
	else if (key_data.key == MLX_KEY_LEFT && ((key_data.action & PRESS) != 0))
		cub->pl.rot = 1;
	else if (key_data.key == MLX_KEY_RIGHT && ((key_data.action & PRESS) != 0))
		cub->pl.rot = -1;
	release_keys(key_data, cub);
}

void	start_the_game(t_cub *cub)
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
