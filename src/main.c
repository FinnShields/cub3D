/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:47:28 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/10 15:45:46 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_vector	*map;
	t_assets	*assets;
	t_data		*data;

	if (argc != 2)
		msg_and_exit("Incorrect number of arguments");
	map = read_map(argv);
	assets = get_assets(map);
	data = init_data(map, assets);
	draw_walls(data);
	mlx_key_hook(data->window, &key_hook, data);
	mlx_loop(data->window);
	mlx_terminate(data->window);
	free_vector(map);
	clean_up_textures(assets);
	free_assets_struct(assets);
	free(data->ray);
	free(data);
}
