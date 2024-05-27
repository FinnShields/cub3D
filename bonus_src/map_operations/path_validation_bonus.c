/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:03:05 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/16 10:41:32 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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

static void	mark_neighbour_if_accessible(t_vector *map, size_t x, size_t y)
{
	char	**arr;

	arr = map->text;
	if ((y < map->used_nodes - 1) && ft_strchr("0PD", arr[y + 1][x]) != NULL)
		arr[y + 1][x] = '#';
	if (x < (ft_strlen(map->text[y]) - 1))
		if (ft_strchr("0PD", arr[y][x + 1]) != NULL)
			arr[y][x + 1] = '#';
	if ((y != 0) && (ft_strchr("0PD", map->text[y - 1][x]) != NULL))
		arr[y - 1][x] = '#';
	if ((x != 0) && (ft_strchr("0PD", map->text[y][x - 1]) != NULL))
		arr[y][x - 1] = '#';
	arr[y][x] = '*';
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
				mark_neighbour_if_accessible(map, x, y);
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
					mark_neighbour_if_accessible(map, x, y);
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
	size_t		door_count;

	map_cpy = copy_vector(map);
	if (map_cpy == NULL)
	{
		error_msg("Malloc failure");
		return (2);
	}
	door_count = count_chars(map_cpy, 'D');
	check_all_from_start(map_cpy);
	if (check_if_char_is_in_map(map_cpy, '0') == true)
		result = false;
	else
		result = true;
	if (result == true && count_chars(map_cpy, 'D') == door_count)
		result = error_msg("Map has no accessible doors");
	if (count_chars(map_cpy, 'P') != 0)
	{
		error_msg("Invalid map - exit can't be reached");
		result = 3;
	}
	free_vector(map_cpy);
	return (result);
}
