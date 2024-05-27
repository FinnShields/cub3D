/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:58:44 by fshields          #+#    #+#             */
/*   Updated: 2024/05/10 15:46:54 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_colour(int rgb[3])
{
	uint32_t	colour;
	uint32_t	a;

	a = 255;
	colour = (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | a);
	return (colour);
}

t_data	*init_data(t_vector *map, t_assets *assets)
{
	t_data	*data;
	t_ray	*ray_data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		ft_exit("Malloc failure", data, assets, map);
	data->window = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", false);
	if (!(data->window))
		ft_exit("Failed to init window", data, assets, map);
	data->map = map;
	data->plane_x = PLANE_X;
	data->plane_y = PLANE_Y;
	set_start_position(data, map);
	data->assets = assets;
	if (init_wall_textures(data) == false)
		ft_exit(NULL, data, assets, map);
	if (init_image(data) == false)
		ft_exit("Failed to create image", data, assets, map);
	ray_data = (t_ray *)malloc(sizeof(t_ray));
	if (ray_data == NULL)
		ft_exit("Malloc failure", data, assets, map);
	data->ray = ray_data;
	return (data);
}
