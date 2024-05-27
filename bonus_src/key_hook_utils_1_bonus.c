/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils_1_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:09:26 by fshields          #+#    #+#             */
/*   Updated: 2024/05/15 15:31:27 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	left_key(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y * sin(-ROT_SPEED);
	data->dir_y = old_dir_x * sin(-ROT_SPEED) + data->dir_y * cos(-ROT_SPEED);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-ROT_SPEED) - \
		data->plane_y * sin(-ROT_SPEED);
	data->plane_y = old_plane_x * sin(-ROT_SPEED) + \
		data->plane_y * cos(-ROT_SPEED);
	draw_walls(data);
}

void	right_key(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y * sin(ROT_SPEED);
	data->dir_y = old_dir_x * sin(ROT_SPEED) + data->dir_y * cos(ROT_SPEED);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(ROT_SPEED) - \
		data->plane_y * sin(ROT_SPEED);
	data->plane_y = old_plane_x * sin(ROT_SPEED) + \
		data->plane_y * cos(ROT_SPEED);
	draw_walls(data);
}

void	w_key(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->pos_x + (data->dir_x * MOVE_SPEED);
	new_pos_y = data->pos_y + (data->dir_y * MOVE_SPEED);
	if (wall_collision(data, new_pos_x, new_pos_y))
		return ;
	data->pos_y = new_pos_y;
	data->pos_x = new_pos_x;
	check_for_win(data);
	draw_walls(data);
	clear_minimap(data);
	display_minimap(data);
}

void	s_key(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->pos_x - (data->dir_x * MOVE_SPEED);
	new_pos_y = data->pos_y - (data->dir_y * MOVE_SPEED);
	if (wall_collision(data, new_pos_x, new_pos_y))
		return ;
	data->pos_y = new_pos_y;
	data->pos_x = new_pos_x;
	check_for_win(data);
	draw_walls(data);
	clear_minimap(data);
	display_minimap(data);
}

void	space_key(t_data *data)
{
	mlx_texture_t	*staff_tex;

	mlx_delete_image(data->window, data->staff);
	if (validate_sprite(2) == false)
		ft_exit("failed to load sprite data", data, 1);
	staff_tex = mlx_load_png("./bonus_src/sprites/staff_2.png");
	if (!staff_tex)
		ft_exit("texture load error", data, 1);
	data->staff = mlx_texture_to_image(data->window, staff_tex);
	mlx_delete_texture(staff_tex);
	if (!data->staff)
		ft_exit("image load error", data, 1);
	if (mlx_resize_image(data->staff, 190, 290) == false)
		ft_exit("image resize error", data, 1);
	if (mlx_image_to_window(data->window, data->staff, 700, 700) == -1)
		ft_exit("image to window error", data, 1);
}
