/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:15:33 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/16 11:14:56 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_assets_struct(t_assets *assets)
{
	if (assets->north_file != NULL)
		free(assets->north_file);
	if (assets->south_file != NULL)
		free(assets->south_file);
	if (assets->east_file != NULL)
		free(assets->east_file);
	if (assets->west_file != NULL)
		free(assets->west_file);
	if (assets->door_file != NULL)
		free(assets->door_file);
	if (assets->portal_file != NULL)
		free(assets->portal_file);
	free(assets);
}

void	map_validation_error(char *msg, t_vector *map, t_assets *assets)
{
	if (assets != NULL)
		free_assets_struct(assets);
	if (map != NULL)
		free_vector(map);
	if (msg != NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(msg, 2);
	}
	exit(1);
}

void	msg_and_exit(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}

bool	error_msg(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	return (false);
}

void	ft_exit(char *msg, t_data *data, int code)
{
	if (msg != NULL)
		error_msg(msg);
	free_vector(data->map);
	clean_up_textures(data->assets);
	free_assets_struct(data->assets);
	if (data->ray != NULL)
		free(data->ray);
	mlx_close_window(data->window);
	mlx_terminate(data->window);
	free(data);
	exit(code);
}
