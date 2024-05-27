/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:55:49 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/16 10:25:50 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../mlx/include/MLX42/MLX42.h"
# include "vector_bonus.h"
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>

# define SCREEN_WIDTH 1300
# define SCREEN_HEIGHT 900
# define PLANE_X 0
# define PLANE_Y 0.66
# define ROT_SPEED 0.1
# define MOVE_SPEED 0.3
# define PLAYER_SIZE 0.2
# define MM_OFFSET 75
# define DBL_MAX 1.7976931348623158e+308

typedef struct s_assets
{
	char			*west_file;
	char			*east_file;
	char			*north_file;
	char			*south_file;
	char			*door_file;
	char			*portal_file;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*door;
	mlx_texture_t	*door_flicker;
	mlx_texture_t	*portal;
	int				floor[3];
	int				ceiling[3];
	char			start_orientation;
}	t_assets;

typedef struct s_ray
{
	double			ray_direction_x;
	double			ray_direction_y;
	double			side_distance_x;
	double			side_distance_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				line_height;
	char			tile_type;
	int				side;
	int				tile_x;
	int				tile_y;
}	t_ray;

typedef struct s_data
{
	mlx_t			*window;
	mlx_image_t		*img;
	mlx_image_t		*mm_wall;
	mlx_image_t		*mm_open;
	mlx_image_t		*mm_player;
	mlx_image_t		*staff;
	t_vector		*map;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			pos_x;
	double			pos_y;
	t_ray			*ray;
	t_assets		*assets;
	double			exit_x;
	double			exit_y;
	int				targeted_x;
	int				targeted_y;
	useconds_t		last_opening_sec;
	useconds_t		last_opening_usec;
	int				open_door_x;
	int				open_door_y;
	bool			is_door_open;
}	t_data;

//error.c
void		msg_and_exit(char *msg);
void		map_validation_error(char *msg, t_vector *map, \
			t_assets *assets);
void		free_assets_struct(t_assets *assets);
bool		error_msg(char *msg);
void		ft_exit(char *msg, t_data *data, int code);

//key_hook
void		key_hook(mlx_key_data_t keydata, void *param);

//key_hook_utils_1.c
void		left_key(t_data *data);
void		right_key(t_data *data);
void		w_key(t_data *data);
void		s_key(t_data *data);
void		space_key(t_data *data);

//key_hook_utils_2.c
void		a_key(t_data *data);
void		d_key(t_data *data);
bool		wall_collision(t_data *data, double new_pos_X, \
			double new_pos_Y);

//map_operations/read_map.c
t_vector	*read_map(char **argv);
bool		check_map_dimensions(t_vector *map);

//map_operations/get_assets.c
char		*trim_identifier(char *config_line, \
			unsigned int id_length);
t_assets	*get_assets(t_vector *map);

//map_operations/validate_format.c
void		validate_texture_info_format(t_vector *map);

//map_operations/get_color_config.c
bool		copy_rgb_values(char *color_info, \
			t_assets *assets, char *id);
bool		validate_trimmed_rgb_info(char *rgb);

//map_operations/clean_up_map.c
bool		clean_up_and_validate_map(t_vector *map);

//map_operations/validate_map_shape.c
bool		validate_map_shape(t_vector *map);
bool		check_around_for_char(t_vector *map, char c, \
			size_t x, size_t y);

//map_operations/path_validation.c
int			check_if_all_map_is_accessible(t_vector *map);

//map_operations/validate_exit_position
bool		validate_exit_position(t_vector *map);

//map_operations/path_validation_utils_bonus.c
size_t		count_chars(t_vector *map, char c);

//map_operations/validate_doors_bonus.c
bool		validate_doors(t_vector *map);

//map_operations/convert_rgb_bonus.c
int			convert_rgb(int *asset, char **strs);

//init.c
t_data		*init_data(t_vector *map, t_assets *assets);
bool		init_wall_textures(t_data *data);

//init_utils.c
void		set_start_position(t_data *data, t_vector *map);
bool		init_image(t_data *data);
uint32_t	get_colour(int rgb[3]);
bool		validate_texture_file(char *path);

//find_walls
void		get_ray_length(int *step_x, int *step_y, t_data *data);
double		adjust_ray_direction(int mode, int x, t_data *data);
double		get_delta_dist(double ray_direction);
double		get_side_distance(t_data *data, int *step, char mode);

//find_walls_utils
bool		check_if_valid_pos(char **map, t_data *data);
void		dda_x(t_ray *ray, int *map_x, int *step_x);
void		dda_y(t_ray *ray, int *map_y, int *step_y);
t_ray		*assign_ray(t_data *data, int *step_x, int *step_y);
bool		check_n_set_tile_type(char **map, int map_x, \
			int map_y, t_ray *ray);

//wall_height.c
void		draw_walls(t_data *data);
void		get_line_height(t_data *data);

//raycasting/draw_floor_and_ceiling.c
void		draw_ceiling(int x, int wall_start, t_data *data);
void		draw_floor(int x, int wall_end, t_data *data);

//draw_textured_wall.c
void		draw_text_sect(int draw_start, int draw_end, int x, \
			t_data *data);

//clean_up_textures.c
void		clean_up_textures(t_assets *assets);

//check_for_win.c
void		check_for_win(t_data *data);

//minimap.c
void		display_minimap(t_data *data);
void		clear_minimap(t_data *data);

//mouse_hook.c
void		mouse_hook(void *param);

//door_mechanism/door_open.c
void		save_targeted_x_and_y(t_data *data);
void		open_door(t_data *data);
useconds_t	get_elapsed_time(t_data *data);
void		play_door_animation(void *param);

//door_mechanism/door_open_utils.c
void		init_door_flicker(t_data *data);

//sprites
void		init_staff(t_data *data);
bool		validate_sprite(int mode);

//game_messages_bonus.c
void		print_start_message(void);

#endif