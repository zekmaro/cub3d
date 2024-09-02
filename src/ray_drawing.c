/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:29:01 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/02 16:17:36 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_texture_coords(t_vars *vars, t_tex_typ texture_index, int *tex_x)
{
	if (texture_index % 2 == 0)
	{
		*tex_x = (int)(vars->ray->ray_x) % vars->unit_size;
		if (texture_index == TEXTURE_SOUTH)
			*tex_x *= -1;
	}
	else if (texture_index % 2 == 1)
	{
		*tex_x = (int)(vars->ray->ray_y) % vars->unit_size;
		if (texture_index == TEXTURE_WEST)
			*tex_x = vars->unit_size - *tex_x;
	}
}

int	is_monster(t_vars *vars, int x, int y)
{
	return (x == vars->map->monster_x && y == vars->map->monster_y);
}

int	get_map_x(t_vars *vars)
{
	return ((int)(vars->ray->ray_x / vars->unit_size));
}

int	get_map_y(t_vars *vars)
{
	return ((int)(vars->ray->ray_y / vars->unit_size));
}

void	draw_ray_column(t_vars *vars, int ray_id, t_tex_typ texture_index)
{
	int				y;
	int				color;
	t_pix_inf		pixel_info;
	t_tex_coords	coords;

	y = vars->ray->draw_start;
	pixel_info.ray_id = ray_id;
	pixel_info.map_x = get_map_x(vars);
	pixel_info.map_y = get_map_y(vars);
	while (y < vars->ray->draw_end)
	{
		color = get_texture_color_at_y(vars, texture_index, y, &coords);
		if (color != -1)
		{
			pixel_info.y = y;
			pixel_info.color = color;
			handle_pixel(vars, &pixel_info);
		}
		y++;
	}
}
