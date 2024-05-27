/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:15:32 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/16 10:37:06 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	trim_empty_lines(t_vector *map)
{
	size_t	i;
	char	*empty_line;

	i = 0;
	while (i == 0 && map->text[i] != NULL)
	{
		if (map->text[0][0] == '\n')
		{
			empty_line = extract_array(map, 0);
			if (empty_line == NULL)
			{
				error_msg("Malloc failure");
				return (-1);
			}
			free(empty_line);
			empty_line = NULL;
		}
		else
			i++;
	}
	return (0);
}

static bool	validate_top_line(t_vector *map)
{
	size_t	i;
	size_t	line_len;

	i = 0;
	if (map->used_nodes < 3)
		return (error_msg("Map too small"));
	line_len = ft_strlen(map->text[0]);
	if (line_len < 2)
		return (error_msg("Invalid map format - top line too small"));
	if (map->text[0][line_len - 1] != '\n')
		return (error_msg("Map too small"));
	while (map->text[0][i] != '\n')
	{
		if (map->text[0][i] != '1' && map->text[0][i] != ' ')
			return (error_msg("Invalid map format - map upper border"));
		i++;
	}
	return (true);
}

static bool	validate_middle_line(char *line)
{
	size_t		i;
	size_t		line_len;

	i = 0;
	line_len = ft_strlen(line);
	if (line_len < 2)
		return (error_msg("Map too small"));
	if (line[line_len - 1] != '\n')
		return (error_msg("Invalid map format - unexpected newline"));
	while (line[i] != '\n')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] != '1')
			return (error_msg("Map must be surrounded by walls(1)"));
		while (line[i] != ' ' && line[i] != '\n')
		{
			if (ft_strchr("NESW10", line[i]) == NULL)
				return (error_msg("Invalid character in map"));
			i++;
		}
		if (i != 0 && line[i - 1] != '1')
			return (error_msg("Map must be surrounded by walls(1)"));
	}
	return (true);
}

static bool	validate_bottom_line(t_vector *map)
{
	size_t	i;
	size_t	line_len;
	char	*bottom_line;

	i = 0;
	bottom_line = map->text[map->used_nodes - 1];
	line_len = ft_strlen(bottom_line);
	if (line_len < 2)
		return (error_msg("Invalid map format"));
	while (bottom_line[i] != '\0')
	{
		if (bottom_line[i] != '1' && bottom_line[i] != ' ')
			return (error_msg("Map must be surrounded by walls(1)"));
		i++;
	}
	return (true);
}

bool	clean_up_and_validate_map(t_vector *map)
{
	size_t	i;

	i = 0;
	if (trim_empty_lines(map) == -1)
		return (false);
	if (check_map_dimensions(map) == false)
		return (false);
	if (validate_top_line(map) == false)
		return (false);
	while (i < (map->used_nodes - 1))
	{
		if (validate_middle_line(map->text[i]) == false)
			return (false);
		i++;
	}
	if (validate_bottom_line(map) == false)
		return (false);
	if (validate_map_shape(map) == false)
		return (false);
	return (true);
}
