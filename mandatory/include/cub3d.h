#ifndef CUB3D_H
#define CUB3D_H

#include <libc.h>
#include "MLX42.h"
#include "errno.h"
#include "get_next_line.h"
#include <math.h>

#define MINI_TILE 10
#define MINI_W MINI_TILE * 10
#define MINI_H MINI_TILE * 10

#define S_W 1400
#define S_H 800
#define FRAMES 20


#define MINIMAPS 10
#define TILE_SIZE 35
#define PI M_PI
#define PLAYER_SPEED 5
#define ROT_SPEED (3 * (PI / 180))
#define FOV ((60 * PI) / 180)
#define NUM_RAYS S_W

#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF
#define RED 0xC0C0C0FF
#define GREEN 0x00FF00FF
#define BLUE 0x0000FFFF
#define YELLOW 0xFFFF00FF
#define CYAN 0x00FFFFFF
#define MAGENTA 0xFF00FFFF
#define GRAY 0x808080FF
#define LIGHT_GRAY 0xC0C0C0FF
#define DARK_GRAY 0x404040FF

#define COLOR

typedef struct s_ray
{
    double ray_ngl;
    double distance;
    int flag;
    double h_interx;
    double h_intery;
    double v_interx;
    double v_intery;

    bool left;
    bool right;
    bool up;
    bool down;
    bool is_vertical;
} ray_t;


typedef struct s_img_data
{
    void *img;
    char *data_ptr;
    int bit_per_pixle;
    int line_size;
} t_img_data;

typedef struct player
{
    int x;
    int y;
    int l_r;
    int u_d;
    int rot;
    double rot_angle;

    int size;
} player;

typedef struct s_textures
{
    void *player;
    void *wall;
    void *space;
} t_textures;

typedef struct map
{
    char **map2d;
    int width;
    int height;
} map_t;

typedef struct cub
{
    mlx_t *mlx;
    player pl;
    map_t map;
    int cur_frame;
    mlx_texture_t *anim[FRAMES];
    mlx_texture_t *textures[4];
    mlx_texture_t *door;

    bool pl_action;
    bool mouse;
    int is_door;
    mlx_image_t *img;
    int ceilling_color;
    int floor_color;
    ray_t ray;
    mlx_key_data_t key;
} t_cub;

typedef struct s_map
{
    char *line;
    size_t size;
    struct s_map *next;
} t_map;

typedef struct data
{
    void *value;
    struct data *next;
} _data;

typedef struct s_data
{
    char **map;
    int map_hieght;
    int map_width;
    int x_player;
    int y_player;
    char *WE;
    char *NO;
    char *SO;
    char *EA;
    char pl_cell;

    int ciel_rgb;
    int floor_color;
} t_data;

void close_func(void *param);
void	free_exit(int exit_stat, t_cub *cub);
void	mouse_handler(mouse_key_t key, action_t action, modifier_key_t mods, void *param);
void	cursor_handler(double xpos, double ypos, void *param);

void	minimap(t_cub *cub);
void	animation(t_cub *cub);
float            horizontal_caster(t_cub *cub, float angle, int *wall_hit);
float            vertical_caster(t_cub *cub, float angle, int *);
int	 wall_inter(t_cub *cub, double x, double y);

double           norm_angle(double angle);
bool	is_wall(t_cub *cub, int x, int y);
void	game_loop(void *param);
void	start_the_game(t_cub *cub);
void	update(t_cub *cub);
void	draw_line(t_cub *cub, int x, int y, int end_x, int end_y);
void	cast_all_rays(t_cub *cub);

void	print_error(char *str, int exit_flag);
char	**get_the_map(char *map_file);
uint32_t         get_rgba(uint32_t rgb);
int	 ft_strncmp(const char *s1, const char *s2, size_t n);
size_t           ft_strlen(const char *s);
void	ft_perror(char *str);
char	*ft_strtrim(const char *s1, const char *set);
size_t           ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
void	ft_free_memory(char **res);
int	 ft_atoi(const char *str);
void	fill_map(char *str, int fd, t_data *map);
int          	ft_strchr(const char *s);
void	*ft_calloc(size_t count, size_t size);
void	*alloc(int mode, int size);
void	check_file_type(char *str);
void	parse_map(t_data *map, char *file);
void	init_map(t_data *map);
char	*ft_itoa(int n);

#endif           /* CUB3D_H */
