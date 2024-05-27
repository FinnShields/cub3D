/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_open_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:24:31 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/15 15:18:28 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

useconds_t	get_elapsed_time(t_data *data)
{
	struct timeval	current_time;
	useconds_t		elapsed_usec;
	useconds_t		elapsed_sec;
	useconds_t		elapsed_milisec;

	gettimeofday(&current_time, NULL);
	elapsed_sec = (current_time.tv_sec - data->last_opening_sec) * 1000;
	if (elapsed_sec == 0)
		elapsed_usec = (current_time.tv_usec - data->last_opening_usec) / 1000;
	else
	{
		elapsed_usec = (1000 - (data->last_opening_usec / 1000)) + \
		(current_time.tv_usec / 1000);
		elapsed_sec -= 1000;
	}
	elapsed_milisec = elapsed_sec + elapsed_usec;
	return (elapsed_milisec);
}

static void	flicker_door(t_data *data, char mode, bool reset_map)
{
	static bool	map_done;
	static bool	disappeared;

	data->map->text[data->open_door_y][data->open_door_x] = mode;
	draw_walls(data);
	if (mode == '0' && !map_done && reset_map == true)
	{
		clear_minimap(data);
		display_minimap(data);
		map_done = true;
		disappeared = true;
	}
	if (mode == 'D' && disappeared && reset_map == true)
	{
		clear_minimap(data);
		display_minimap(data);
		disappeared = false;
		map_done = false;
	}
}

void	play_door_animation(void *param)
{
	useconds_t	elapsed_millisec;
	t_data		*data;

	data = (t_data *)param;
	if (data->is_door_open == false)
		return ;
	elapsed_millisec = get_elapsed_time(data);
	if (elapsed_millisec < 1000)
	{
		if (elapsed_millisec % 200 == 0)
			return (flicker_door(data, 'd', false));
		else if (elapsed_millisec % 100 == 0)
			return (flicker_door(data, 'D', false));
	}
	if (elapsed_millisec < 6000)
		return (flicker_door(data, '0', true));
	data->is_door_open = false;
	if ((int)data->pos_x == data->open_door_x && \
	(int)data->pos_y == data->open_door_y)
	{
		ft_printf("GAME OVER - YOU GOT STUCK IN A RE-MATERIALIZING WALL\n");
		mlx_close_window(data->window);
	}
	flicker_door(data, 'D', true);
}

void	save_targeted_x_and_y(t_data *data)
{
	data->targeted_x = data->ray->tile_x;
	data->targeted_y = data->ray->tile_y;
}

void	open_door(t_data *data)
{
	struct timeval	anim_start;

	if (data->is_door_open == true)
		return ;
	if (data->map->text[data->targeted_y][data->targeted_x] != 'D')
		return ;
	data->open_door_x = data->targeted_x;
	data->open_door_y = data->targeted_y;
	gettimeofday(&anim_start, NULL);
	data->is_door_open = true;
	data->last_opening_sec = anim_start.tv_sec;
	data->last_opening_usec = anim_start.tv_usec;
	flicker_door(data, 'd', false);
}
