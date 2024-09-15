/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:52:49 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/16 00:08:46 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_door_list(t_vars *vars, t_door *door_list, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		if (door_list[i].open && door_list[i].offset < vars->unit_size)
			door_list[i].offset += 8;
		else if (!door_list[i].open && door_list[i].offset > 0)
			door_list[i].offset -= 8;
	}
}

int	inside_door(t_vars *vars, t_ray_params *params)
{
	if (vars->doors[params->index].orientation == 0)
	{
		return (params->door_flag && ((params->ray_x % vars->unit_size \
				< (vars->unit_size - vars->doors[params->index].offset))));
	}
	else if (vars->doors[params->index].orientation == 1)
	{
		return (params->door_flag && ((params->ray_y % vars->unit_size \
				< (vars->unit_size - vars->doors[params->index].offset))));
	}
	return (0);
}

int	get_door_id(t_vars *vars, int ray_x, int ray_y)
{
	int	i;

	i = 0;
	while (i < vars->map->num_doors)
	{
		if (abs(vars->doors[i].center_x - ray_x) < vars->unit_size \
			&& abs(vars->doors[i].center_y - ray_y) < vars->unit_size)
			return (i);
		i++;
	}
	return (0);
}
