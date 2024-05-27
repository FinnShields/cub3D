/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:15:33 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/10 15:26:11 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_exit(char *msg, t_data *data, t_assets *assts, t_vector *map)
{
	if (msg != NULL)
		error_msg(msg);
	free_vector(map);
	free_assets_struct(assts);
	mlx_close_window(data->window);
	mlx_terminate(data->window);
	free(data);
	exit(1);
}
