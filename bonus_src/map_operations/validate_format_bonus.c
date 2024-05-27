/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_format_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:04:42 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/13 11:14:13 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static bool	check_if_possibly_asset_info_line(char *str)
{
	if (*str != '\n')
	{
		if (ft_isalpha(*str) == true && ft_strlen(str) > 3)
			return (true);
		else
			return (false);
	}
	return (false);
}

void	validate_texture_info_format(t_vector *map)
{
	size_t	i;
	int		texture_info_line;

	i = 0;
	texture_info_line = 0;
	while (i < map->used_nodes)
	{
		if (check_if_possibly_asset_info_line(map->text[i]) == true)
			texture_info_line++;
		else
		{
			if (map->text[i][0] != '\n')
				break ;
		}
		i++;
	}
	if (texture_info_line != 8)
		map_validation_error("Invalid texture config data", map, NULL);
	while (i < map->used_nodes)
	{
		if (check_if_possibly_asset_info_line(map->text[i]) == true)
			map_validation_error("Invalid texture config data", map, NULL);
		i++;
	}
}
