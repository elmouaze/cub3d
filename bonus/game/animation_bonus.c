/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:20:21 by abennar           #+#    #+#             */
/*   Updated: 2025/01/25 11:08:08 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint	rgb2rgba(mlx_texture_t *texture, int x, int y)
{
	int			pixel_index;
	uint32_t	alpha;
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;

	pixel_index = (y * texture->width + x) * 4;
	alpha = texture->pixels[pixel_index + 0];
	red = texture->pixels[pixel_index + 1];
	green = texture->pixels[pixel_index + 2];
	blue = texture->pixels[pixel_index + 3];
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

void	render_a_frame(t_cub *cub, mlx_texture_t *cur_frame)
{
	uint32_t	h;
	uint32_t	w;
	uint		color;

	h = 0;
	w = 0;
	while (h < cur_frame->height)
	{
		w = 0;
		while (w < cur_frame->width)
		{
			color = rgb2rgba(cur_frame, w, h);
			if (color && color != 0xFFFFFF00)
				mlx_put_pixel(cub->img, (S_W - cur_frame->width) / 2 + w, \
					S_H - cur_frame->height + h, color);
			w++;
		}
		h++;
	}
}

void	animation(t_cub *cub)
{
	if (!cub->pl_action)
	{
		render_a_frame(cub, cub->anim[0]);
		cub->cur_frame = 0;
	}
	else
	{
		render_a_frame(cub, cub->anim[cub->cur_frame]);
		cub->cur_frame++;
		if (cub->cur_frame == FRAMES)
		{
			cub->pl_action = false;
			cub->cur_frame = 0;
		}
	}
}
