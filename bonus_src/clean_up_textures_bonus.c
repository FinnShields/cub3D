/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_textures_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:17:40 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/16 11:13:36 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	clean_up_textures(t_assets *assets)
{
	if (assets->north != NULL)
		mlx_delete_texture(assets->north);
	if (assets->east != NULL)
		mlx_delete_texture(assets->east);
	if (assets->south != NULL)
		mlx_delete_texture(assets->south);
	if (assets->west != NULL)
		mlx_delete_texture(assets->west);
	if (assets->door != NULL)
		mlx_delete_texture(assets->door);
	if (assets->portal != NULL)
		mlx_delete_texture(assets->portal);
	if (assets->door_flicker != NULL)
		mlx_delete_texture(assets->door_flicker);
}
