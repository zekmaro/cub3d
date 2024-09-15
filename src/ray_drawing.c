/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:29:01 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/12 13:45:51 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_texture_coords(t_vars *vars, t_tex_typ texture_index, int *tex_x)
{
	if (texture_index % 2 == 0)
	{
		*tex_x = (int)(vars->ray->ray_x) % vars->unit_size;
		if (texture_index == TEXTURE_SOUTH)
		{
			*tex_x *= -1;
			*tex_x -= 1;
		}
	}
	else if (texture_index % 2 == 1)
	{
		*tex_x = (int)(vars->ray->ray_y) % vars->unit_size;
		if (texture_index == TEXTURE_WEST)
		{
			*tex_x = vars->unit_size - *tex_x;
			*tex_x -= 1;
		}
	}
}

t_tex_typ	define_texture_type(t_vars *vars)
{
	int	map_x;
	int	map_y;
	int	dx;
	int	dy;

	map_x = (int)vars->ray->ray_x / vars->unit_size;
	map_y = (int)vars->ray->ray_y / vars->unit_size;
	if (vars->map->grid[map_y][map_x] == '1')
	{
		dx = (int)vars->ray->last_ray_x / vars->unit_size - map_x;
		dy = (int)vars->ray->last_ray_y / vars->unit_size - map_y;
		if (dy == 1)
			return (TEXTURE_NORTH);
		else if (dx == 1)
			return (TEXTURE_WEST);
		else if (dy == -1)
			return (TEXTURE_SOUTH);
		else if (dx == -1)
			return (TEXTURE_EAST);
	}
	else if (vars->map->grid[map_y][map_x] == 'D')
	{
		dx = (int)vars->ray->last_ray_x / vars->unit_size - map_x;
		dy = (int)vars->ray->last_ray_y / vars->unit_size - map_y;
		if (dy == 1)
			return (TEXTURE_DOOR0);
		else if (dx == 1)
			return (TEXTURE_DOOR1);
		else if (dy == -1)
			return (TEXTURE_DOOR2);
		else if (dx == -1)
			return (TEXTURE_DOOR3);
	}
	return (TEXTURE_NONE);
}

int	get_map_x(t_vars *vars)
{
	return ((int)(vars->ray->ray_x / vars->unit_size));
}

int	get_map_y(t_vars *vars)
{
	return ((int)(vars->ray->ray_y / vars->unit_size));
}
