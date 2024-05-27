/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_walls_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:21:57 by fshields          #+#    #+#             */
/*   Updated: 2024/05/13 16:00:33 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

double	adjust_ray_direction(int mode, int x, t_data *data)
{
	double	camera_x;

	camera_x = 2 * x / (double) SCREEN_WIDTH - 1;
	if (mode == 1)
		return (data->dir_x + data->plane_x * camera_x);
	return (data->dir_y + data->plane_y * camera_x);
}

double	get_delta_dist(double ray_direction)
{
	if (ray_direction == 0)
		return (DBL_MAX);
	else
		return (fabs(1 / ray_direction));
}

double	get_side_distance(t_data *data, int *step, char mode)
{
	double	ray_direction;
	double	position;

	if (mode == 'x')
	{
		ray_direction = data->ray->ray_direction_x;
		position = data->pos_x;
	}
	else
	{
		ray_direction = data->ray->ray_direction_y;
		position = data->pos_y;
	}
	if (ray_direction < 0)
	{
		*step = -1;
		return ((position - ((int) position)) * get_delta_dist(ray_direction));
	}
	else
	{
		*step = 1;
		return ((((int)position) + 1.0 - position) * \
		get_delta_dist(ray_direction));
	}
}

static double	adjust_for_camera_plane(t_data *data, char mode)
{
	double	delta_distance;
	t_ray	*ray;

	ray = data->ray;
	if (mode == 'x')
		delta_distance = get_delta_dist(ray->ray_direction_x);
	else
		delta_distance = get_delta_dist(ray->ray_direction_y);
	if (mode == 'x')
		return (ray->side_distance_x - delta_distance);
	else
		return (ray->side_distance_y - delta_distance);
}

void	get_ray_length(int *step_x, int *step_y, t_data *data)
{
	bool		hit;
	int			map_x;
	int			map_y;
	t_ray		*ray;
	t_vector	*map;

	map = data->map;
	ray = assign_ray(data, step_x, step_y);
	hit = false;
	map_x = (int) data->pos_x;
	map_y = (int) data->pos_y;
	while (hit == false)
	{
		if (ray->side_distance_x < ray->side_distance_y)
			dda_x(ray, &map_x, step_x);
		else
			dda_y(ray, &map_y, step_y);
		if (check_if_valid_pos(map->text, data) && \
		check_n_set_tile_type(map->text, map_x, map_y, ray) == true)
			hit = true;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (adjust_for_camera_plane(data, 'x'));
	else
		ray->perp_wall_dist = (adjust_for_camera_plane(data, 'y'));
}
