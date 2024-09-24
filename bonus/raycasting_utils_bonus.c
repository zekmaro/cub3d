/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:41:47 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/24 17:01:31 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	update_door_status(t_vars *vars, int index)
{
	int	dy;
	int	dx;

	dy = vars->doors[index].center_y - vars->player->center_y;
	dx = vars->doors[index].center_x - vars->player->center_x;
	vars->doors[index].distance_to_door = sqrt(dy * dy + dx * dx);
	if (vars->doors[index].distance_to_door < 150)
		vars->doors[index].open = 1;
	else
		vars->doors[index].open = 0;
}

static void	update_ray_position(t_vars *vars)
{
	vars->ray->last_ray_x = vars->ray->ray_x;
	vars->ray->last_ray_y = vars->ray->ray_y;
	vars->ray->ray_x += vars->ray->ray_dir_x;
	vars->ray->ray_y += vars->ray->ray_dir_y;
}

static void	initialize_ray(t_vars *vars)
{
	vars->ray->ray_x = vars->player->x;
	vars->ray->ray_y = vars->player->y;
	vars->ray->ray_dir_x = cos(vars->ray->ray_angle);
	vars->ray->ray_dir_y = sin(vars->ray->ray_angle);
}

void	get_ray_target_coords(t_vars *vars)
{
	t_ray_params	params;
	int				index;
	int				door_flag;

	door_flag = 0;
	index = 0;
	initialize_ray(vars);
	while (!is_wall(vars, vars->ray->ray_y, vars->ray->ray_x))
	{
		params.door_flag = door_flag;
		params.ray_y = vars->ray->ray_y;
		params.ray_x = vars->ray->ray_x;
		params.index = index;
		if (inside_door(vars, &params))
			break ;
		update_ray_position(vars);
		door_flag = is_door(vars, vars->ray->ray_y, vars->ray->ray_x);
		if (door_flag)
		{
			index = get_door_id(vars, vars->ray->ray_x, vars->ray->ray_y);
			if (index == -1)
				break ;
			update_door_status(vars, index);
		}
	}
}
