/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:51:27 by abennar           #+#    #+#             */
/*   Updated: 2024/11/20 11:12:14 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mouse_handler(mouse_key_t key, action_t action, modifier_key_t mods, void *param)
{
	t_cub *cub;
	
	cub = (t_cub*)param;
	(void)mods;
	if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		cub->mouse = true;
	if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		cub->mouse = false;
}

void	cursor_handler(double xpos, double ypos, void *param)
{
	t_cub *cub;

	(void)ypos;
	cub = (t_cub*)param;
	if (xpos > S_W / 2)
		cub->pl.rot = -1;
	else
		cub->pl.rot = 1;
}