/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moua <ael-moua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:29:35 by abennar           #+#    #+#             */
/*   Updated: 2025/01/17 02:22:44 by ael-moua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"
#include "cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (b);
}

void	free_exit(int exit_stat, t_cub *cub)
{
	int i = -1;
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
	ft_memset(cub, 0, sizeof(t_cub));
    exit(exit_stat);
}

uint32_t 	get_rgba(uint32_t rgb)
{
	return (rgb << 8) | 255;
}



void	trans_data(t_data *data, t_cub *cub)
{
	ft_memset(cub, 0, sizeof(t_cub));
	if (data->pl_cell == 'N')
		cub->pl.rot_angle = 4.71238898038;
	else if (data->pl_cell == 'S')
		cub->pl.rot_angle = 1.57079632679;
	else if (data->pl_cell == 'E')
		cub->pl.rot_angle = 0;
	else
		cub->pl.rot_angle = M_PI;
	 cub->map.height = data->map_hieght;
	 cub->map.width = data->map_width;
	 cub->pl.x = data->x_player * TILE_SIZE;
	 cub->pl.y = data->y_player * TILE_SIZE; 
	 cub->map.map2d= data->map;
	 cub->textures[0] = mlx_load_png(data->NO);
	 cub->textures[1] = mlx_load_png(data->SO);
	 cub->textures[2] = mlx_load_png(data->WE);
	 cub->textures[3] = mlx_load_png(data->EA);
	 cub->door = mlx_load_png("./textures/door.png");
	if (!cub->textures[0] || !cub->textures[1] || !cub->textures[2] || !cub->textures[3])
		free_exit(1, cub);
	cub->ceilling_color = get_rgba(data->ciel_rgb);
	cub->floor_color = get_rgba(data->floor_color);
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
		char *png_path = ft_strjoin(path, ft_strjoin(ft_itoa(i), ".png"));
		cub->anim[i] = mlx_load_png(png_path);
		if (!cub->anim[i])
			free_exit(1, cub);
		i++;
	}
}

void close_func(void *param)
{
	t_cub *cub;

	cub = (t_cub *)param;

	free_exit(0, cub);
}

void check_leaks()
{
	system("leaks cub3d");
	
}

int main(int ac, char **av)
{
	t_cub	cub;
	t_data   map;

	// atexit(check_leaks);

   if (ac != 2)
        ft_perror("Error: Bad args");
    check_file_type(av[1]);
    init_map(&map);
    parse_map(&map, av[1]);
	trans_data(&map, &cub);

	import_sprites(&cub);
	start_the_game(&cub);
}