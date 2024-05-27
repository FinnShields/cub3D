/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:00:40 by fshields          #+#    #+#             */
/*   Updated: 2024/05/15 15:30:17 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	init_mm_images(t_data *data, int mm_square)
{
	data->mm_wall = mlx_new_image(data->window, mm_square, mm_square);
	if (!data->mm_wall)
		ft_exit("image creation error", data, 1);
	ft_memset(data->mm_wall->pixels, 175, data->mm_wall->width * \
		data->mm_wall->height * sizeof(int32_t));
	data->mm_open = mlx_new_image(data->window, mm_square, mm_square);
	if (!data->mm_open)
		ft_exit("image creation error", data, 1);
	ft_memset(data->mm_open->pixels, 200, data->mm_open->width * \
		data->mm_open->height * sizeof(int32_t));
	data->mm_player = mlx_new_image(data->window, mm_square, mm_square);
	if (!data->mm_player)
		ft_exit("image creation error", data, 1);
	ft_memset(data->mm_player->pixels, 255, data->mm_player->width * \
		data->mm_player->height * sizeof(int32_t));
}

static void	place_line_of_images(t_data *data, size_t y, int mm_square)
{
	size_t		x;
	t_vector	*map;

	x = 0;
	map = data->map;
	while (map->text[y][x] != '\0')
	{
		if (data->map->text[y][x] == '1' || data->map->text[y][x] == 'D' \
		|| data->map->text[y][x] == 'd')
		{
			if (mlx_image_to_window(data->window, data->mm_wall, (MM_OFFSET + x \
			* mm_square), (MM_OFFSET + y * mm_square)) == -1)
				ft_exit("error with image instance", data, 1);
		}
		else if (map->text[y][x] != ' ' && map->text[y][x] != '\n')
		{
			if (mlx_image_to_window(data->window, data->mm_open, (MM_OFFSET + x \
			* mm_square), (MM_OFFSET + y * mm_square)) == -1)
				ft_exit("error with image instance", data, 1);
		}
		x ++;
	}
}

void	display_minimap(t_data *data)
{
	size_t		y;
	int			mm_square;
	t_vector	*map;

	mm_square = 8;
	map = data->map;
	if (map->used_nodes > 50 || ft_strlen(map->text[0]) > 50)
		mm_square = 4;
	init_mm_images(data, mm_square);
	y = 0;
	while (y < map->used_nodes)
		place_line_of_images(data, y++, mm_square);
	if (mlx_image_to_window(data->window, data->mm_player, ((int) data->pos_x * \
	mm_square) + MM_OFFSET, ((int) data->pos_y * mm_square) + MM_OFFSET) == -1)
		ft_exit("error with image instance", data, 1);
}

void	clear_minimap(t_data *data)
{
	mlx_delete_image(data->window, data->mm_open);
	mlx_delete_image(data->window, data->mm_player);
	mlx_delete_image(data->window, data->mm_wall);
}
