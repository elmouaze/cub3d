/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:36:05 by ael-moua          #+#    #+#             */
/*   Updated: 2025/01/24 10:11:40 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libc.h>
# include "../../libs/MLX42.h"
# include "get_next_line.h"
# include <math.h>

# define MINI_TILE	10
# define MINI_W		100
# define MINI_H		100

# define S_W		1400
# define S_H		800
# define FRAMES		20

# define MINIMAPS	10
# define TILE_SIZE	35
# define PLAYER_SPEED 5
# define ROT_SPEED	0.05235987756 	//  (3 * (PI / 180))
# define FOV 		1.0471975512	// ((60 * PI) / 180)
# define NUM_RAYS S_W

# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF
# define RED 0xC0C0C0FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF
# define YELLOW 0xFFFF00FF
# define CYAN 0x00FFFFFF
# define MAGENTA 0xFF00FFFF
# define GRAY 0x808080FF
# define LIGHT_GRAY 0xC0C0C0FF
# define DARK_GRAY 0x404040FF

typedef struct ray
{
	double	ray_ngl;
	double	distance;
	int		flag;
	double	h_interx;
	double	h_intery;
	double	v_interx;
	double	v_intery;
	bool	left;
	bool	right;
	bool	up;
	bool	down;
	bool	is_vertical;
}	t_ray;

struct	s_wall_data
{
	mlx_texture_t	*texture;
	int				dist_p;
	int				wall_height;
	int				wall_top;
	int				wall_bottom;
	float			distance_from_top;
	float			x_offset;
};

typedef struct player
{
	int		x;
	int		y;
	int		l_r;
	int		u_d;
	int		rot;
	double	rot_angle;
	int		size;
}		t_player;

typedef struct s_map
{
	char	**map2d;
	int		width;
	int		height;
}		t_map;

typedef struct cub
{
	mlx_t			*mlx;
	t_player		pl;
	t_map			map;
	int				cur_frame;
	mlx_texture_t	*anim[FRAMES];
	mlx_texture_t	*textures[4];
	mlx_texture_t	*door;
	bool			pl_action;
	bool			mouse;
	int				is_door;
	mlx_image_t		*img;
	int				ceilling_color;
	int				floor_rgb;
	t_ray			ray;
	mlx_key_data_t	key;
	float			x_step;
	float			y_step;
	int				pxl;
}	t_cub;

typedef struct s_parse_map
{
	char				*line;
	size_t				size;
	struct s_parse_map	*next;
}		t_parse_map;

typedef struct gbc_data
{
	void				*value;
	struct gbc_data		*next;
}		t_gbc_data;

typedef struct s_data
{
	char	**map;
	int		map_hieght;
	int		map_width;
	int		x_player;
	int		y_player;
	char	*we;
	char	*no;
	char	*so;
	char	*ea;
	char	pl_cell;
	int		ciel_rgb;
	int		floor_rgb;
}			t_data;

// uint32_t         get_rgba(uint32_t rgb);
// bonus 

void			minimap(t_cub *cub);
void			animation(t_cub *cub);
void			mouse_handler(mouse_key_t key, action_t action, \
modifier_key_t mods, void *param);
void			cursor_handler(double xpos, double ypos, void *param);

// game 

void			start_the_game(t_cub *cub);
void			cast_all_rays(t_cub *cub);
void			update(t_cub *cub);
int				wall_inter(t_cub *cub, double x, double y);
mlx_texture_t	*get_texture(t_cub *cub);
double			norm_angle(double angle);
float			horizontal_caster(t_cub *cub, float angle, int *wall_hit);
float			vertical_caster(t_cub *cub, float angle, int *wall_hit);
void			render_walls(t_cub *cub, int x);
void			wall_env(t_cub *cub, struct s_wall_data *data);

// parsing 

void			check_file_type(char *str);
void			init_map(t_data *map);
void			parse_map(t_data *map, char *file);
int				is_player(char c);
int				check_end(char *line);
void			add_token(t_parse_map **lst, t_parse_map *new);
t_parse_map		*new_node(char *line, size_t len);
char			*ft_fill(char *str);

// utils

void			*ft_memset(void *b, int c, size_t len);
char			*ft_itoa(int n);
void			*alloc(int mode, int size);
void			ft_perror(char *str);
void			free_exit(int exit_stat, t_cub *cub);
void			close_func(void *param);
size_t			ft_strlen(const char *s);
void			*ft_calloc(size_t count, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
char			*ft_strtrim(const char *s1, const char *set);
void			fill_map(char *str, int fd, t_data *map);

#endif           /* CUB3D_H */
