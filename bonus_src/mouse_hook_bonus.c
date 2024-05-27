/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:57:49 by fshields          #+#    #+#             */
/*   Updated: 2024/05/14 13:52:13 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_view_mouse(t_data *data, int mouse_x, int old_x, int *start)
{
	double	change;
	double	old_dir_x;
	double	old_plane_x;

	if (*start == 0)
	{
		*start = 1;
		return ;
	}
	change = 0.005 * abs(old_x - mouse_x);
	if (mouse_x < old_x)
		change *= -1;
	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	data->dir_x = data->dir_x * cos(change) - data->dir_y * sin(change);
	data->dir_y = old_dir_x * sin(change) + data->dir_y * cos(change);
	data->plane_x = data->plane_x * cos(change) - data->plane_y * sin(change);
	data->plane_y = old_plane_x * sin(change) + data->plane_y * cos(change);
	draw_walls(data);
}

void	mouse_hook(void *param)
{
	t_data			*data;
	static int32_t	x;
	static int32_t	y;
	int32_t			old_x;
	static int		start;

	old_x = x;
	data = param;
	mlx_get_mouse_pos(data->window, &x, &y);
	if (x >= 0 && x <= SCREEN_WIDTH && x != old_x && y >= 0 \
	&& y <= SCREEN_HEIGHT)
		update_view_mouse(data, x, old_x, &start);
}
