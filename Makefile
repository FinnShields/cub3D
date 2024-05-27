NAME			=	cub3D
BONUS_NAME		=	cub3D_bonus
GLFW_DIR		=	/Users/$(USER)/.brew/opt/glfw/lib
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
SRCS			=	src/main.c \
					src/error.c \
					src/clean_up_textures.c \
					src/init.c \
					src/init_utils.c \
					src/key_hook.c \
					src/key_hook_utils_1.c \
					src/key_hook_utils_2.c \
					src/raycasting/find_walls.c \
					src/raycasting/find_walls_utils.c \
					src/raycasting/wall_height.c \
					src/raycasting/draw_floor_and_ceiling.c \
					src/raycasting/draw_textured_wall.c \
					src/vector_expand.c \
					src/vector_decrease.c \
					src/vector_copy.c \
					src/map_operations/read_map.c \
					src/map_operations/get_assets.c \
					src/map_operations/get_color_config.c \
					src/map_operations/validate_format.c \
					src/map_operations/clean_up_map.c \
					src/map_operations/validate_map_shape.c \
					src/map_operations/path_validation.c \
					src/map_operations/convert_rgb.c
BONUS_SRCS		=	bonus_src/main_bonus.c \
					bonus_src/error_bonus.c \
					bonus_src/clean_up_textures_bonus.c \
					bonus_src/init_bonus.c \
					bonus_src/init_utils_bonus.c \
					bonus_src/key_hook_bonus.c \
					bonus_src/key_hook_utils_1_bonus.c \
					bonus_src/key_hook_utils_2_bonus.c \
					bonus_src/check_for_win_bonus.c \
					bonus_src/raycasting/find_walls_bonus.c \
					bonus_src/raycasting/find_walls_utils_bonus.c \
					bonus_src/raycasting/wall_height_bonus.c \
					bonus_src/raycasting/draw_floor_and_ceiling_bonus.c \
					bonus_src/raycasting/draw_textured_wall_bonus.c \
					bonus_src/vector_expand_bonus.c \
					bonus_src/vector_decrease_bonus.c \
					bonus_src/vector_copy_bonus.c \
					bonus_src/map_operations/read_map_bonus.c \
					bonus_src/map_operations/get_assets_bonus.c \
					bonus_src/map_operations/get_color_config_bonus.c \
					bonus_src/map_operations/validate_format_bonus.c \
					bonus_src/map_operations/clean_up_map_bonus.c \
					bonus_src/map_operations/validate_map_shape_bonus.c \
					bonus_src/map_operations/path_validation_bonus.c \
					bonus_src/map_operations/validate_exit_position.c \
					bonus_src/map_operations/path_validation_utils_bonus.c \
					bonus_src/map_operations/validate_doors_bonus.c \
					bonus_src/map_operations/convert_rgb_bonus.c \
					bonus_src/door_mechanism/door_open_bonus.c \
					bonus_src/door_mechanism/door_open_utils_bonus.c \
					bonus_src/minimap/minimap_bonus.c \
					bonus_src/mouse_hook_bonus.c \
					bonus_src/sprites/sprites_bonus.c \
					bonus_src/game_messages_bonus.c

OBJS			=	$(SRCS:.c=.o)
BONUS_OBJS		=	$(BONUS_SRCS:.c=.o)
HEADER			=	src/cub3d.h
BONUS_HEADER	=	bonus_src/cub3d_bonus.h
LIBFT_DIR		=	libft
LIBFT_H			=	$(LIBFT_DIR)/libft.h
LIBFT			=	$(LIBFT_DIR)/libft.a
MLX				=	mlx/build/libmlx42.a
MLX_HEADER		=	mlx/include/MLX42/MLX42.h
FSAN			=	-g -fsanitize=address -static-libsan

all:			makelibft $(NAME)

makelibft:
					@make -C ./$(LIBFT_DIR)

$(MLX):
					@cd mlx && cmake -B build && cmake --build build -j4

$(NAME):		$(OBJS) $(LIBFT) $(HEADER) $(LIBFT_H) $(MLX)
					@$(CC) $(OBJS) $(MLX) $(LIBFT) -ldl -pthread -lm -L$(GLFW_DIR) -lglfw -I $(MLX_HEADER) -o $(NAME)
					@echo "⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂"
					@echo "⚂  compiled !  ⚂"
					@echo "⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂"

%.o:			%.c
					@$(CC) $(CFLAGS) -g -c $< -o $@

clean:
					@rm -f $(OBJS)
					@rm -f $(BONUS_OBJS)
					@make clean -C ./$(LIBFT_DIR)
          
san:			$(BONUS_OBJS) $(LIBFT) $(BONUS_HEADER) $(LIBFT_H) $(MLX)
					@$(CC) $(FSAN) $(BONUS_OBJS) $(MLX) $(LIBFT) -ldl -pthread -lm -L$(GLFW_DIR) -lglfw -I $(MLX_HEADER) -o san

fclean:			clean
					@rm -f $(NAME)
					@rm -f $(BONUS_NAME)
					@rm -rf mlx/build
					@make fclean -C ./$(LIBFT_DIR)

re:				fclean all

tidymake:	
					@make clean
					@make all
					@make clean

bonus:			makelibft .bonus

.bonus:			$(BONUS_OBJS) $(LIBFT) $(BONUS_HEADER) $(LIBFT_H) $(MLX)
					@$(CC) $(BONUS_OBJS) $(MLX) $(LIBFT) -ldl -pthread -lm -L$(GLFW_DIR) -lglfw -I $(MLX_HEADER) -o $(BONUS_NAME)
					@echo "⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂"
					@echo "⚂  bonus compiled !  ⚂"
					@echo "⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂⚂"
					@touch .bonus



.PHONY:			all makelibft clean fclean re tidymake san bonus