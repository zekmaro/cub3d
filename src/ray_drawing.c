/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:29:01 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/02 15:39:08 by iberegsz         ###   ########.fr       */
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
	int			y;
	int			tex_x;
	int			tex_y;
	int			color;
	t_pix_inf	pix_inf;

	y = vars->ray->draw_start;
	pix_inf.ray_id = ray_id;
	pix_inf.map_x = get_map_x(vars);
	pix_inf.map_y = get_map_y(vars);
	while (y < vars->ray->draw_end)
	{
		color = get_texture_color_at_y(vars, texture_index, y, &tex_x, &tex_y);
		if (color != -1)
		{
			pix_inf.y = y;
			pix_inf.color = color;
			handle_pixel(vars, &pix_inf);
		}
		y++;
	}
}
