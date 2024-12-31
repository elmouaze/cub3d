#ifndef CUB3D_H
#define CUB3D_H

#include <libc.h>
#include "MLX42.h"
#include "errno.h"
// #include <mlx.h>
#include <math.h>

#define HEIGHT  00
#define WIDTH   1040

#define MINI_TILE 10
#define MINI_W  MINI_TILE * 10
#define MINI_H   MINI_TILE * 10


#define	LINE_SIZE  5
// #define S_W	(10 * SQR_SIZE)
// #define S_H (10 * SQR_SIZE)

#define S_W	1400
#define S_H 800
#define FRAMES 75



// #define MAP_W  10
// #define MAP_H  10

#define MINIMAPS        10
#define	SQR_SIZE		70
#define	PI 				M_PI
#define	PLAYER_R		8
#define PLAYER_SPEED	5
#define ROT_SPEED		(2 * (PI / 180))
#define	MOV_SPEED		2
#define FOV				((60 * PI) / 180)
#define	NUM_RAYS		S_W


# define BLACK        0x000000FF
# define WHITE        0xFFFFFFFF
# define RED          0xC0C0C0FF
# define GREEN        0x00FF00FF
# define BLUE         0x0000FFFF
# define YELLOW       0xFFFF00FF
# define CYAN         0x00FFFFFF
# define MAGENTA      0xFF00FFFF
# define GRAY         0x808080FF
# define LIGHT_GRAY   0xC0C0C0FF
# define DARK_GRAY    0x404040FF

#define COLOR


typedef enum e_type
{
    NO,
    SO,
    WE,
    EA,
    F,
    C,
    VOID,
    NEW_LINE,
    ERR,
    MAP
}   e_type;

typedef struct s_ray
{
	double			ray_ngl;
	double			distance;
	int				flag;
	double              h_interx;
	double              h_intery;
	double              v_interx;
	double              v_intery;

    bool    left;
    bool    right;
    bool    up;
    bool    down;
	bool	is_vertical;
}					ray_t;

typedef struct s_elements{
    char *line;
    e_type type;
    struct s_elements *next;
}t_elements;

typedef	struct s_img_data
{
	void	*img;
	char	*data_ptr;
	int		bit_per_pixle;
	int		line_size;	
}	t_img_data;

typedef	struct player
{
	int     x;
	int     y;
	int     l_r;
	int	    u_d;
    int     rot;
    double   rot_angle;

	int	size;
}	player;

typedef struct s_textures{
    void *player;
    void *wall;
    void *space;
}t_textures;

typedef struct map
{
	char	**map2d;
	int		width;
	int		height;
}		map_t;

typedef struct cub
{
    mlx_t			*mlx;
    player			pl;
	map_t			map;
    int				cur_frame;
    mlx_texture_t   *anim[FRAMES];
    mlx_texture_t   *textures[4];

	bool			pl_action;
	bool			mouse;

	mlx_image_t		*img;

    // char    **map;
	int	ceilling_color;
	int floor_color;
    ray_t       ray;
	t_elements	*elemnts;
	t_elements	*textus;
    mlx_key_data_t key;
}   t_cub;

void	mouse_handler(mouse_key_t key, action_t action, modifier_key_t mods, void *param);
void	cursor_handler(double xpos, double ypos, void *param);

void	minimap(t_cub *cub);
void    animation(t_cub *cub);
float	horizontal_caster(t_cub *cub, float angle);
float	vertical_caster(t_cub *cub, float angle);
bool	wall_inter(t_cub *cub, double x, double y);

double		norm_angle(double angle);
bool is_wall(t_cub *cub, int x, int y);
void	game_loop(void *param);
// void	mlx_put_pixel(t_img_data this, int x, int y , int color);
void	start_the_game(t_cub *cub);
void	update(t_cub *cub);
void draw_line(t_cub *cub, int x, int y, int end_x, int end_y);
// void draw_line(t_cub *cub, long x, long y, long end_x, long end_y);
void	cast_all_rays(t_cub *cub);

void print_error(char *str,int exit_flag);
char **get_the_map(char *map_file);




#endif /* CUB3D_H */
