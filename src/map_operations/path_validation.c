/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:03:05 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/08 10:34:20 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	check_if_char_is_in_map(t_vector *map, char c)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (y < map->used_nodes)
	{
		while (map->text[y][x] != '\0')
		{
			if (map->text[y][x] == c)
				return (true);
			x++;
		}
		y++;
		x = 0;
	}
	return (false);
}

static void	mark_neighbour_if_char(t_vector *map, char c, size_t x, size_t y)
{
	if ((y < (map->used_nodes - 1)) && (map->text[y + 1][x] == c))
		map->text[y + 1][x] = '#';
	if ((x < (ft_strlen(map->text[y]) - 1)) && (map->text[y][x + 1] == c))
		map->text[y][x + 1] = '#';
	if ((y != 0) && (map->text[y - 1][x] == c))
		map->text[y - 1][x] = '#';
	if ((x != 0) && (map->text[y][x - 1] == c))
		map->text[y][x - 1] = '#';
	map->text[y][x] = '*';
}

static void	check_start(t_vector *map)
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
				mark_neighbour_if_char(map, '0', x, y);
				return ;
			}
			x++;
		}
		y++;
		x = 0;
	}
	return ;
}

static void	check_all_from_start(t_vector *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	check_start(map);
	while (check_if_char_is_in_map(map, '#') == true)
	{
		while (y < map->used_nodes)
		{
			while (map->text[y][x] != '\0')
			{
				if (map->text[y][x] == '#')
					mark_neighbour_if_char(map, '0', x, y);
				x++;
			}
			y++;
			x = 0;
		}
		y = 0;
		x = 0;
	}
}

int	check_if_all_map_is_accessible(t_vector *map)
{
	t_vector	*map_cpy;
	int			result;

	map_cpy = copy_vector(map);
	if (map_cpy == NULL)
	{
		error_msg("Malloc failure");
		return (2);
	}
	check_all_from_start(map_cpy);
	if (check_if_char_is_in_map(map_cpy, '0') == true)
		result = false;
	else
		result = true;
	free_vector(map_cpy);
	return (result);
}
