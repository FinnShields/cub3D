/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_doors_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:36:11 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/15 09:43:12 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

bool	validate_doors(t_vector *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (y < map->used_nodes)
	{
		while (map->text[y][x] != '\0')
		{
			if (map->text[y][x] == 'D')
			{
				if (check_around_for_char(map, 'D', x, y) == true)
					return (error_msg("Doors can't be placed adjacently"));
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (true);
}
