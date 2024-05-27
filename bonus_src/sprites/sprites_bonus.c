/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:37:30 by fshields          #+#    #+#             */
/*   Updated: 2024/05/15 15:34:38 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

bool	validate_sprite(int mode)
{
	int	fd;

	if (mode == 1)
		fd = open("./bonus_src/sprites/staff_1.png", O_RDONLY);
	else
		fd = open("./bonus_src/sprites/staff_2.png", O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

void	init_staff(t_data *data)
{
	mlx_texture_t	*staff_tex;

	if (validate_sprite(1) == false)
		ft_exit("error loading sprite", data, 1);
	staff_tex = mlx_load_png("./bonus_src/sprites/staff_1.png");
	if (!staff_tex)
		ft_exit("error loading texture", data, 1);
	data->staff = mlx_texture_to_image(data->window, staff_tex);
	mlx_delete_texture(staff_tex);
	if (!data->staff)
		ft_exit("image load error", data, 1);
	if (mlx_resize_image(data->staff, 200, 300) == false)
		ft_exit("image resize error", data, 1);
	if (mlx_image_to_window(data->window, data->staff, 750, 650) == -1)
		ft_exit("image to window error", data, 1);
}
