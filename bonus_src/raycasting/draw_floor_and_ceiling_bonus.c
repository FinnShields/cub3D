/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_ceiling_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:08:02 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/13 10:38:34 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_ceiling(int x, int wall_start, t_data *data)
{
	int			y;
	uint32_t	colour;
	t_assets	*assets;

	y = 0;
	assets = data->assets;
	colour = get_colour(assets->ceiling);
	while (y < wall_start)
	{
		mlx_put_pixel(data->img, x, y, colour);
		y++;
	}
}

void	draw_floor(int x, int wall_end, t_data *data)
{
	uint32_t	colour;
	t_assets	*assets;

	assets = data->assets;
	colour = get_colour(assets->floor);
	while (wall_end < (SCREEN_HEIGHT - 1))
	{
		mlx_put_pixel(data->img, x, wall_end, colour);
		wall_end++;
	}
}
