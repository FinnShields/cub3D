/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:47:28 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/15 15:37:44 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	data->is_door_open = false;
	print_start_message();
	draw_walls(data);
	init_staff(data);
	display_minimap(data);
	mlx_key_hook(data->window, &key_hook, data);
	mlx_loop_hook(data->window, &mouse_hook, data);
	mlx_loop_hook(data->window, &play_door_animation, data);
	mlx_loop(data->window);
	ft_exit(NULL, data, 0);
}
