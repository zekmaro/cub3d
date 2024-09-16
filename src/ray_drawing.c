/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:29:01 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/16 14:23:16 by iberegsz         ###   ########.fr       */
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

static t_tex_typ	get_wall_texture(int dx, int dy)
{
	if (dy == 1)
		return (TEXTURE_NORTH);
	else if (dx == 1)
		return (TEXTURE_WEST);
	else if (dy == -1)
		return (TEXTURE_SOUTH);
	else if (dx == -1)
		return (TEXTURE_EAST);
	return (TEXTURE_NONE);
}

static t_tex_typ	get_door_texture(t_vars *vars, int dx, int dy, int index)
{
	if (dy == 1)
		return (TEXTURE_DOOR0);
	else if (dx == 1)
		return (TEXTURE_DOOR1);
	else if (dy == -1)
		return (TEXTURE_DOOR2);
	else if (dx == -1)
		return (TEXTURE_DOOR3);
	else if (vars->doors[index].orientation == 1)
		return (TEXTURE_DOOR0);
	else if (vars->doors[index].orientation == 0)
		return (TEXTURE_DOOR1);
	return (TEXTURE_NONE);
}

t_tex_typ	define_texture_type(t_vars *vars)
{
	int	map_x;
	int	map_y;
	int	index;
	int	dx;
	int	dy;

	map_x = (int)vars->ray->ray_x / vars->unit_size;
	map_y = (int)vars->ray->ray_y / vars->unit_size;
	dx = (int)vars->ray->last_ray_x / vars->unit_size - map_x;
	dy = (int)vars->ray->last_ray_y / vars->unit_size - map_y;
	if (vars->map->grid[map_y][map_x] == '1')
		return (get_wall_texture(dx, dy));
	else if (vars->map->grid[map_y][map_x] == 'D')
	{
		index = get_door_id(vars, vars->ray->ray_x, vars->ray->ray_y);
		return (get_door_texture(vars, dx, dy, index));
	}
	return (TEXTURE_NONE);
}
