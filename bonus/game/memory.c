/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:58:12 by abennar           #+#    #+#             */
/*   Updated: 2025/01/24 08:58:35 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_exit(int exit_stat, t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (cub->textures[i])
			mlx_delete_texture(cub->textures[i]);
	}
	i = -1;
	while (++i < FRAMES)
	{
		if (cub->anim[i])
			mlx_delete_texture(cub->anim[i]);
	}
	if (cub->door)
		mlx_delete_texture(cub->door);
	if (cub->img)
		mlx_delete_image(cub->mlx, cub->img);
	if (cub->mlx)
		mlx_terminate(cub->mlx);
	alloc(0, 0);
	exit(exit_stat);
}

void	close_func(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	free_exit(0, cub);
}
