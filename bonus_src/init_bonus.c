/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:58:44 by fshields          #+#    #+#             */
/*   Updated: 2024/05/16 11:19:25 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	set_exit_position(t_data *data, t_vector *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (y < map->used_nodes)
	{
		while (map->text[y][x] != '\0')
		{
			if (map->text[y][x] == 'P')
			{
				data->exit_x = (double) x;
				data->exit_y = (double) y;
				return ;
			}
			x++;
		}
		y++;
		x = 0;
	}
	return ;
}

static mlx_texture_t	*init_texture(char *file, char *id)
{
	mlx_texture_t	*texture;

	if (validate_texture_file(file) == false)
		return (NULL);
	texture = mlx_load_png(file);
	if (texture == NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd(id, 2);
		ft_putendl_fd("could not be loaded as mlx_texture_t", 2);
	}
	return (texture);
}

bool	init_wall_textures(t_data *data)
{
	t_assets	*assets;

	assets = data->assets;
	assets->north = init_texture(assets->north_file, "north");
	if (assets->north == NULL)
		return (false);
	assets->south = init_texture(assets->south_file, "south");
	if (assets->south == NULL)
		return (false);
	assets->west = init_texture(assets->west_file, "west");
	if (assets->west == NULL)
		return (false);
	assets->east = init_texture(assets->east_file, "east");
	if (assets->east == NULL)
		return (false);
	assets->door = init_texture(assets->door_file, "door");
	if (assets->door == NULL)
		return (false);
	assets->door_flicker = init_texture(assets->door_file, "door flicker");
	if (assets->door_flicker == NULL)
		return (false);
	assets->portal = init_texture(assets->portal_file, "exit");
	if (assets->portal == NULL)
		return (false);
	return (true);
}

t_data	*init_data(t_vector *map, t_assets *assets)
{
	t_data	*data;
	t_ray	*ray_data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		map_validation_error("Malloc failure", map, assets);
	ray_data = (t_ray *)malloc(sizeof(t_ray));
	if (ray_data == NULL)
		ft_exit("Malloc failure", data, 1);
	data->ray = ray_data;
	data->window = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", false);
	if (!(data->window))
		ft_exit("Failed to init window", data, 1);
	data->map = map;
	data->plane_x = PLANE_X;
	data->plane_y = PLANE_Y;
	set_start_position(data, map);
	set_exit_position(data, map);
	data->assets = assets;
	if (init_wall_textures(data) == false)
		ft_exit(NULL, data, 1);
	if (init_image(data) == false)
		ft_exit("Failed to create image", data, 1);
	init_door_flicker(data);
	return (data);
}
