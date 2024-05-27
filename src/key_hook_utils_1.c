/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:09:26 by fshields          #+#    #+#             */
/*   Updated: 2024/05/10 15:50:43 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	draw_walls(data);
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
	draw_walls(data);
}
