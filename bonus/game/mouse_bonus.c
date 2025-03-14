/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:51:27 by abennar           #+#    #+#             */
/*   Updated: 2025/01/25 11:08:08 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	mouse_handler(mouse_key_t key, action_t action, \
modifier_key_t mods, void *param)
{
	t_cub	*cub;

	cub = (t_cub *) param;
	(void) mods;
	if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		cub->mouse = true;
	if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		cub->mouse = false;
}

void	cursor_handler(double xpos, double ypos, void *param)
{
	t_cub	*cub;

	cub = (t_cub *) param;
	if (cub->mouse)
	{
		(void) ypos;
		cub = (t_cub *)param;
		if (xpos > S_W / 2)
			cub->pl.rot = -1;
		else
			cub->pl.rot = 1;
	}
	else
	{
		cub->pl.rot = 0;
	}
}
