/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_assets_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:46:21 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/16 11:12:05 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*trim_identifier(char *config_line, unsigned int id_len)
{
	char	*temp;
	char	*trimmed;
	size_t	len;

	len = ft_strlen(config_line);
	temp = ft_substr(config_line, id_len, (ft_strlen(config_line) - id_len));
	free(config_line);
	if (temp == NULL)
		return (NULL);
	trimmed = ft_strtrim(temp, " \n");
	free(temp);
	if (trimmed == NULL)
		return (NULL);
	return (trimmed);
}

static char	*extract_config(char *id, t_assets *assets, t_vector *map)
{
	size_t	i;
	char	*texture_info;
	char	*trimmed_info;

	i = 0;
	while (i < map->used_nodes)
	{
		if (ft_strncmp(id, map->text[i], 3) == 0)
		{
			if (ft_strlen(map->text[i]) < 4)
				break ;
			texture_info = extract_array(map, i);
			if (texture_info == NULL)
				map_validation_error("Malloc failure", map, assets);
			trimmed_info = trim_identifier(texture_info, 3);
			if (trimmed_info == NULL)
				map_validation_error("Malloc failure", map, assets);
			return (trimmed_info);
		}
		i++;
	}
	map_validation_error("Missing config information", map, assets);
	return (NULL);
}

static void	extract_rgb(char *id, t_assets *assets, t_vector *map)
{
	size_t	i;
	char	*color_info;
	char	*trimmed_info;

	i = 0;
	while (i < map->used_nodes)
	{
		if (ft_strncmp(id, map->text[i], 2) == 0)
		{
			if (ft_strlen(map->text[i]) < 7)
				break ;
			color_info = extract_array(map, i);
			if (color_info == NULL)
				map_validation_error("Malloc failure", map, assets);
			trimmed_info = trim_identifier(color_info, 2);
			if (trimmed_info == NULL)
				map_validation_error("Malloc failure", map, assets);
			if (copy_rgb_values(trimmed_info, assets, id) == false)
				map_validation_error(NULL, map, assets);
			return ;
		}
		i++;
	}
	map_validation_error("Missing config information", map, assets);
}

void	get_texture_info(t_vector *map, t_assets *assets)
{
	assets->north_file = extract_config("NO ", assets, map);
	assets->south_file = extract_config("SO ", assets, map);
	assets->east_file = extract_config("EA ", assets, map);
	assets->west_file = extract_config("WE ", assets, map);
	assets->door_file = extract_config("DO ", assets, map);
	assets->portal_file = extract_config("PO ", assets, map);
	extract_rgb("F ", assets, map);
	extract_rgb("C ", assets, map);
	if (clean_up_and_validate_map(map) == false)
	{
		free_assets_struct(assets);
		free_vector(map);
		exit(1);
	}
}

t_assets	*get_assets(t_vector *map)
{
	t_assets	*assets;

	validate_texture_info_format(map);
	assets = (t_assets *)malloc(sizeof(t_assets));
	if (assets == NULL)
		map_validation_error("Malloc failure", map, NULL);
	assets->east_file = NULL;
	assets->north_file = NULL;
	assets->west_file = NULL;
	assets->south_file = NULL;
	assets->door_file = NULL;
	assets->portal_file = NULL;
	assets->north = NULL;
	assets->south = NULL;
	assets->east = NULL;
	assets->west = NULL;
	assets->door = NULL;
	assets->door_flicker = NULL;
	assets->portal = NULL;
	get_texture_info(map, assets);
	return (assets);
}
