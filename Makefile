

SRCS =  mandatory/game/game.c \
		mandatory/game/hooks.c \
		mandatory/game/horizontal.c \
		mandatory/game/memory.c \
		mandatory/game/raycasting.c \
		mandatory/game/textures.c \
		mandatory/game/vertical.c \
		mandatory/main.c \
		mandatory/parse/get_next_line/get_next_line.c \
		mandatory/parse/get_next_line/get_next_line_utils.c \
		mandatory/parse/map.c \
		mandatory/parse/map_utils.c \
		mandatory/parse/memory_and_errors.c \
		mandatory/parse/parse.c \
		mandatory/utils/ft_atoi.c \
		mandatory/utils/ft_calloc.c \
		mandatory/utils/ft_itoa.c \
		mandatory/utils/ft_memset.c \
		mandatory/utils/ft_split.c \
		mandatory/utils/ft_strlcpy.c \
		mandatory/utils/ft_strlen.c \
		mandatory/utils/ft_strncmp.c \
		mandatory/utils/ft_strtrim.c \
		mandatory/utils/ft_substr.c


BONUS_SRCS =	bonus/game/animation_bonus.c \
			bonus/game/game_bonus.c \
			bonus/game/hooks_bonus.c \
			bonus/game/horizontal_bonus.c \
			bonus/game/memory_bonus.c \
			bonus/game/minimap_bonus.c \
			bonus/game/mouse_bonus.c \
			bonus/game/raycasting_bonus.c \
			bonus/game/textures_bonus.c \
			bonus/game/vertical_bonus.c \
			bonus/main_bonus.c \
			bonus/parse/get_next_line/get_next_line_bonus.c \
			bonus/parse/get_next_line/get_next_line_utils_bonus.c \
			bonus/parse/map_bonus.c \
			bonus/parse/map_utils_bonus.c \
			bonus/parse/memory_and_errors_bonus.c \
			bonus/parse/parse_bonus.c \
			bonus/utils/ft_atoi_bonus.c \
			bonus/utils/ft_calloc_bonus.c \
			bonus/utils/ft_itoa_bonus.c \
			bonus/utils/ft_memset_bonus.c \
			bonus/utils/ft_split_bonus.c \
			bonus/utils/ft_strlcpy_bonus.c \
			bonus/utils/ft_strlen_bonus.c \
			bonus/utils/ft_strncmp_bonus.c \
			bonus/utils/ft_strtrim_bonus.c \
			bonus/utils/ft_substr_bonus.c


CC = cc
CFLAGS = -Wall -Wextra -Werror  

MND_INCLUDE = -I mandatory/include/
BONUS_INCLUDE = -I bonus/include/ 

OBJS = $(SRCS:mandatory/%.c=mandatory/%.o)
OBJ_BONUS = $(BONUS_SRCS:bonus/%.c=bonus/%.o)

# MLX_LIB =	/Users/Desktop/cub3d/libs/MLX42/build/libmlx42.a
# GLFW_LIB = -L "/Users/abennar/goinfre/homebrew/opt/glfw/lib/" 

GLFW_LIB = libs/libglfw3.a
MLX_LIB = libs/libmlx42.a

FRAMEWORK = $(MLX_LIB) $(GLFW_LIB) -framework Cocoa -framework OpenGL -framework IOKit #-lglfw


NAME = cub3d
NAME_BONUS = cub3d_bonus

all: mlx $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(FRAMEWORK) -o $@ $(OBJS)

mlx : 
# cd libs/MLX42 && cmake -B build && cmake --build build -j4 
	

bonus: $(NAME_BONUS)

$(NAME_BONUS): mlx $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(FRAMEWORK) -o $@ $(OBJ_BONUS)

mandatory/%.o: mandatory/%.c mandatory/include/cub3d.h mandatory/include/get_next_line.h
	$(CC) $(CFLAGS) $(MND_INCLUDE) -c $< -o $@

bonus/%.o: bonus/%.c bonus/include/cub3d_bonus.h bonus/include/get_next_line.h
	$(CC) $(CFLAGS) $(BONUS_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJ_BONUS)

fclean: clean
	rm -rf /Users/abennar/Desktop/cub3d/libs/MLX42/build
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

