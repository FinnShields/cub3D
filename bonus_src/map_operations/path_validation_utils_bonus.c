/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:10:02 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/13 12:40:57 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

size_t	count_chars(t_vector *map, char c)
{
	size_t	x;
	size_t	y;
	size_t	count;

	x = 0;
	y = 0;
	count = 0;
	while (y < map->used_nodes)
	{
		while (map->text[y][x] != '\0')
		{
			if (map->text[y][x] == c)
				count++;
			x++;
		}
		y++;
		x = 0;
	}
	return (count);
}
