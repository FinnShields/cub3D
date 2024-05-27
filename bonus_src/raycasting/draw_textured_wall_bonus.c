/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_wall_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:43:02 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/14 16:16:38 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static double	get_wall_x(int side, t_data *data, t_ray *ray)
{
	double	wall_x;

	if (side == 0)
		wall_x = data->pos_y + ray->perp_wall_dist * ray->ray_direction_y;
	else
		wall_x = data->pos_x + ray->perp_wall_dist * ray->ray_direction_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	get_texture_x(int side, t_data *data, int tex_w)
{
	int		texture_x;
	double	wall_x;
	t_ray	*ray;

	ray = data->ray;
	wall_x = get_wall_x(side, data, ray);
	texture_x = (int)(wall_x * ((double) tex_w));
	if (side == 0 && (ray->ray_direction_x > 0))
		texture_x = tex_w - texture_x - 1;
	if (side == 1 && (ray->ray_direction_y < 0))
		texture_x = tex_w - texture_x - 1;
	return (texture_x);
}

uint32_t	get_element_by_coordinate(int x, int y, uint32_t *arr, int tex_w)
{
	uint32_t	colour;
	int			index;

	if (y == 0)
		index = x;
	else
		index = (y * tex_w) + x;
	colour = arr[index];
	return (colour);
}

static mlx_texture_t	*select_texture(t_data *data)
{
	t_assets	*assets;
	t_ray		*ray;
	char		**map;

	assets = data->assets;
	ray = data->ray;
	map = data->map->text;
	if (ray->tile_type == 'D')
		return (assets->door);
	if (ray->tile_type == 'd')
		return (assets->door_flicker);
	if (ray->tile_type == 'P')
		return (assets->portal);
	if (ray->side == 1 && ray->ray_direction_y < 0)
		return (assets->north);
	if (ray->side == 1 && ray->ray_direction_y > 0)
		return (assets->south);
	if (ray->side == 0 && ray->ray_direction_x < 0)
		return (assets->east);
	else
		return (assets->west);
}

void	draw_text_sect(int draw_start, int draw_end, int x, t_data *data)
{
	double			texture_position;
	int				texture_y;
	int				texture_x;
	uint32_t		color;
	mlx_texture_t	*texture;

	texture = select_texture(data);
	texture_x = get_texture_x(data->ray->side, data, texture->width);
	texture_position = (draw_start - SCREEN_HEIGHT / 2 + data->ray->line_height \
		/ 2) * ((double) texture->height / data->ray->line_height);
	while (draw_start < draw_end)
	{
		if (x == (SCREEN_WIDTH / 2) && draw_start == (SCREEN_HEIGHT / 2))
			save_targeted_x_and_y(data);
		texture_y = (int)texture_position & (texture->height - 1);
		texture_position += (double) texture->height / data->ray->line_height;
		color = get_element_by_coordinate(texture_x, texture_y, \
			(uint32_t *)texture->pixels, texture->width);
		color = (color << 24) | (((color >> 16) << 24) >> 16) | \
			(((color << 16) >> 24) << 16) | (color >> 24);
		mlx_put_pixel(data->img, x, draw_start, color);
		draw_start++;
	}
}
