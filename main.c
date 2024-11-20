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

int main(int ac, char **av)
{
	t_cub	cub;
	t_data   map;

   if (ac != 2)
        ft_perror("Error");
    check_file_type(av[1]);
    init_map(&map);
    parse_map(&map, av[1]);
    print_data(&map);
	
	cub.pl.l_r = 0;
	cub.pl.rot_angle = PI;
	cub.pl.size = 0;
	cub.pl.u_d = 0;
	cub.cur_frame = 0;
	cub.pl_action = 0;
	
	 cub.map.height = map.map_hieght;
	 cub.map.width = map.map_width;
	 cub.pl.x = map.x_player;
	 cub.pl.y = map.y_player; 
	 cub.map.map2d=map.map;
	 cub.textures[0] = mlx_load_png(map.NO);
	 cub.textures[1] = mlx_load_png(map.SO);
	 cub.textures[2] = mlx_load_png(map.WE);
	 cub.textures[3] = mlx_load_png(map.EA);
	cub.ceilling_color =map.ciel_rgb;
	cub.floor_color = map.floor_color;

	cub.mouse = false;
	
	cub.mlx = mlx_init(S_W, S_H, "cub3d", 0);
	//import_freams(&cub);
	start_the_game(&cub);
	mlx_loop(cub.mlx);
}