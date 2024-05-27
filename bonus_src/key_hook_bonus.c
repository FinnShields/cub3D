/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:40:41 by fshields          #+#    #+#             */
/*   Updated: 2024/05/15 15:00:41 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->window);
	if (mlx_is_key_down(data->window, MLX_KEY_LEFT))
		left_key(data);
	if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
		right_key(data);
	if (mlx_is_key_down(data->window, MLX_KEY_W))
		w_key(data);
	if (mlx_is_key_down(data->window, MLX_KEY_S))
		s_key(data);
	if (mlx_is_key_down(data->window, MLX_KEY_D))
		d_key(data);
	if (mlx_is_key_down(data->window, MLX_KEY_A))
		a_key(data);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		space_key(data);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
	{
		mlx_delete_image(data->window, data->staff);
		open_door(data);
		init_staff(data);
	}
}
