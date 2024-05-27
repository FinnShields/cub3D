/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:09:04 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/15 14:48:07 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_2d_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	if (arr != NULL)
		free(arr);
}

static size_t	get_array_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

static bool	validate_values(char **strs, t_assets *assets, char *id)
{
	size_t	i;
	int		*asset;

	i = 0;
	if (id[0] == 'F')
		asset = assets->floor;
	else
		asset = assets->ceiling;
	if (convert_rgb(asset, strs) == false)
		return (false);
	i = 0;
	while (i < 3)
	{
		if (ft_strlen(strs[i]) > 3)
			return (error_msg("Invalid RGB values"));
		if (asset[i] < 0 || asset[i] > 255)
			return (error_msg("Invalid RGB values"));
		i++;
	}
	return (true);
}

bool	copy_rgb_values(char *trimmed_info, t_assets *assets, char *id)
{
	char	**num_strs;
	size_t	i;
	int		return_value;

	if (validate_trimmed_rgb_info(trimmed_info) == false)
		return (error_msg("Invalid RGB configuration"));
	return_value = -1;
	num_strs = ft_split(trimmed_info, ',');
	free(trimmed_info);
	if (num_strs == NULL)
		return (error_msg("Malloc failure"));
	if (get_array_size(num_strs) != 3)
	{
		free_2d_array(num_strs);
		return (error_msg("Invalid RGB configuration"));
	}
	i = 0;
	return_value = false;
	if (validate_values(num_strs, assets, id) == true)
		return_value = true;
	free_2d_array(num_strs);
	return (return_value);
}

bool	validate_trimmed_rgb_info(char *rgb)
{
	bool	result;
	size_t	comma_count;
	size_t	i;

	comma_count = 0;
	i = 0;
	result = true;
	while (rgb[i] != '\0')
	{
		if (rgb[i] == ',')
			comma_count++;
		if (ft_isdigit(rgb[i]) == false && rgb[i] != ',')
		{
			result = false;
			break ;
		}
		i++;
	}
	if (comma_count > 2)
		result = false;
	if (result == false)
		free(rgb);
	return (result);
}
