/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_walls_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:11:31 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/14 15:24:47 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

bool	check_if_valid_pos(char **map, t_data *data)
{
	int	i;
	int	j;
	int	map_x;
	int	map_y;

	i = 0;
	j = 0;
	map_x = (int) data->pos_x;
	map_y = (int) data->pos_y;
	while (map[j] != NULL)
		j++;
	if (j < map_y)
		return (false);
	while (map[map_y][i] != '\0')
		i++;
	if (i < map_x)
		return (false);
	return (true);
}

void	dda_x(t_ray *ray, int *map_x, int *step_x)
{
	ray->side_distance_x += get_delta_dist(ray->ray_direction_x);
	*map_x += *step_x;
	ray->side = 0;
}

void	dda_y(t_ray *ray, int *map_y, int *step_y)
{
	ray->side_distance_y += get_delta_dist(ray->ray_direction_y);
	*map_y += *step_y;
	ray->side = 1;
}

t_ray	*assign_ray(t_data *data, int *step_x, int *step_y)
{
	t_ray	*ray;

	ray = data->ray;
	ray->side = -1;
	ray->side_distance_x = get_side_distance(data, step_x, 'x');
	ray->side_distance_y = get_side_distance(data, step_y, 'y');
	return (ray);
}

bool	check_n_set_tile_type(char **map, int map_x, int map_y, t_ray *ray)
{
	ray->tile_x = map_x;
	ray->tile_y = map_y;
	if (map[map_y][map_x] == '1')
	{
		ray->tile_type = '1';
		return (true);
	}
	if (map[map_y][map_x] == 'D')
	{
		ray->tile_type = 'D';
		return (true);
	}
	if (map[map_y][map_x] == 'd')
	{
		ray->tile_type = 'd';
		return (true);
	}
	if (map[map_y][map_x] == 'P')
	{
		ray->tile_type = 'P';
		return (true);
	}
	return (false);
}
