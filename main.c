/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:29:35 by abennar           #+#    #+#             */
/*   Updated: 2024/11/20 14:08:16 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"
#include "PARSE/cube3d.h"
#include <stdlib.h>

uint32_t 	get_rgb(uint32_t rgb)
{
	return (rgb << 8) | 255;
}

void	trans_data(t_data *data, t_cub *cub)
{
	cub->pl.l_r = 0;
	cub->pl.rot_angle = PI;
	cub->pl.size = 0;
	cub->pl.u_d = 0;
	cub->cur_frame = 0;
	cub->pl_action = 0;
	
	 cub->map.height = data->map_hieght;
	 cub->map.width = data->map_width;
	 cub->pl.x = data->x_player * SQR_SIZE;
	 cub->pl.y = data->y_player * SQR_SIZE; 
	 cub->map.map2d= data->map;
	 cub->textures[0] = mlx_load_png(data->NO);
	 cub->textures[1] = mlx_load_png(data->SO);
	 cub->textures[2] = mlx_load_png(data->WE);
	 cub->textures[3] = mlx_load_png(data->EA);

	if (!cub->textures[0] || !cub->textures[1] || !cub->textures[2] || !cub->textures[3])
	{
		exit(1);
	}

	cub->ceilling_color = get_rgb(data->ciel_rgb);
	cub->floor_color = get_rgb(data->floor_color);


	cub->mouse = false;
}

void print_data(t_data *data)
{
    if (data == NULL)
    {
        printf("Data is NULL\n");
        return;
    }

    printf("Player Position: (%d, %d)\n", data->x_player, data->y_player);
    
    printf("West Texture: %s\n", data->WE ? data->WE : "NULL");
    printf("North Texture: %s\n", data->NO ? data->NO : "NULL");
    printf("South Texture: %s\n", data->SO ? data->SO : "NULL");
    printf("East Texture: %s\n", data->EA ? data->EA : "NULL");

    printf("Ciel RGB: %d\n", data->ciel_rgb);
    printf("Floor Color: %d\n", data->floor_color);

    if (data->map != NULL)
    {
        printf("Map:\n");
        for (int i = 0; i < data->map_hieght; ++i)
        {
            if (data->map[i] != NULL)
                printf("%s\n", data->map[i]);
        }
    }
    else
    {
        printf("No map data available.\n");
    }
}

void	import_sprites(t_cub *cub)
{
	int i;
	char *path = ft_strndup("./frames/", 9);

	i = 0;
	while (i < FRAMES)
	{
		char *png_path = ft_strjoin(path, ft_strjoin(ft_itoa(i), ft_strndup(".png", 4)));
		printf("PNG path : %s\n", png_path);
		cub->anim[i] = mlx_load_png(png_path);
		if (!cub->anim[i])
			exit(1);
		i++;
	}
}

int main(int ac, char **av)
{
	t_cub	cub;
	t_data   map;

   if (ac != 2)
        ft_perror("Error");
    check_file_type(av[1]);
    init_map(&map);
    parse_map(&map, av[1]);
	
	trans_data(&map, &cub);

	cub.mouse = false;
	
	printf("%s\n", "after\n");
	import_sprites(&cub);


	cub.mlx = mlx_init(S_W, S_H, "cub3d", 0);
	start_the_game(&cub);
	mlx_loop(cub.mlx);
}