/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:17:40 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/10 15:20:36 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_up_textures(t_assets *assets)
{
	mlx_delete_texture(assets->north);
	mlx_delete_texture(assets->east);
	mlx_delete_texture(assets->south);
	mlx_delete_texture(assets->west);
}
