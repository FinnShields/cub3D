/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_exit_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:38:45 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/13 12:54:14 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

bool	validate_exit_position(t_vector *map)
{
	bool	is_exit_found;
	size_t	i;
	size_t	j;

	is_exit_found = false;
	i = 0;
	j = 0;
	while (i < map->used_nodes)
	{
		while (map->text[i][j] != '\0')
		{
			if (map->text[i][j] == 'P')
			{
				if (is_exit_found == true)
					return (error_msg("More than one exit position"));
				is_exit_found = true;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (is_exit_found == false)
		return (error_msg("Missing exit position"));
	return (true);
}
