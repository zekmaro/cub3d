/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:29:01 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/02 12:30:28 by iberegsz         ###   ########.fr       */
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
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;
	int	map_x;
	int	map_y;

	y = vars->ray->draw_start;
	map_x = get_map_x(vars);
	map_y = get_map_y(vars);
	while (y < vars->ray->draw_end)
	{
		get_texture_coords(vars, texture_index, &tex_x);
		tex_y = (int)((y - vars->ray->draw_start) * vars->unit_size \
			/ vars->ray->line_height);
		color = get_texture_color(vars->textures[texture_index], tex_x, tex_y);
		if (color != -1)
		{
			if (is_monster(vars, map_x, map_y))
			{
				put_pixel_to_image(vars, ray_id, y, color);
			}
			else
			{
				put_pixel_to_image(vars, ray_id, y, color);
			}
		}
		y++;
	}
}
