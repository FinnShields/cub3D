/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_open_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:17:41 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/15 13:06:38 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	*ft_texture_color_set(void *dest, size_t len)
{
	uint8_t	*buffer;
	size_t	i;

	buffer = (uint8_t *) dest;
	i = 0;
	while (len > i)
	{
		buffer[i] = 255;
		i++;
		i++;
		buffer[i] = 255;
		i++;
		buffer[i] = 255;
		i++;
	}
	return (buffer);
}

void	init_door_flicker(t_data *data)
{
	int	pixel_count;

	pixel_count = data->assets->door->height * data->assets->door->width * 4;
	data->assets->door_flicker->pixels = \
	ft_texture_color_set(data->assets->door_flicker->pixels, pixel_count);
}
