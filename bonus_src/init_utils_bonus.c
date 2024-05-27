/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:33:03 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/15 13:52:35 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	set_start_orientation(t_data *data, char c)
{
	if (c == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -PLANE_Y;
		data->plane_y = 0;
	}
	else if (c == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = PLANE_Y;
		data->plane_y = 0;
	}
	else if (c == 'E')
	{
		data->dir_x = 1.0;
		data->dir_y = 0.0;
	}
	else if (c == 'W')
	{
		data->dir_x = -1.0;
		data->dir_y = 0.0;
		data->plane_y *= -1;
	}
}

void	set_start_position(t_data *data, t_vector *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (y < map->used_nodes)
	{
		while (map->text[y][x] != '\0')
		{
			if (ft_strchr("NSEW", map->text[y][x]) != NULL)
			{
				data->pos_x = (double) x + 0.5 - (PLAYER_SIZE / 2);
				data->pos_y = (double) y + 0.5 - (PLAYER_SIZE / 2);
				set_start_orientation(data, map->text[y][x]);
				return ;
			}
			x++;
		}
		y++;
		x = 0;
	}
	return ;
}

bool	validate_texture_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd("file \"", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd("\" cannot be opened", 2);
		return (false);
	}
	close(fd);
	return (true);
}

uint32_t	get_colour(int rgb[3])
{
	uint32_t	colour;
	uint32_t	a;

	a = 255;
	colour = (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | a);
	return (colour);
}

bool	init_image(t_data *data)
{
	data->img = mlx_new_image(data->window, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->img == NULL)
		return (false);
	if (mlx_image_to_window(data->window, data->img, 0, 0) == -1)
		return (false);
	return (true);
}
