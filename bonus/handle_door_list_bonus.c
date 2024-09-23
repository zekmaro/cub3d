/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:52:49 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/23 16:06:37 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_closed_door(t_vars *vars, int y, int x)
{
	int	door_id;

	if (vars == NULL || vars->doors == NULL)
		return (0);
	if (is_door(vars, y, x))
	{
		door_id = get_door_id(vars, x, y);
		if (door_id == -1)
			return (0);
		if (!vars->doors[door_id].open)
			return (1);
	}
	return (0);
}

void	update_door_list(t_vars *vars, t_door *door_list, int size)
{
	int		i;

	if (vars == NULL || vars->doors == NULL)
		return ;
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
	if (vars == NULL || vars->doors == NULL)
		return (0);
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

	if (vars == NULL || vars->doors == NULL)
		return (-1);
	i = 0;
	while (i < vars->map->num_doors)
	{
		if (ft_abs(vars->doors[i].center_x - ray_x) < vars->unit_size \
			&& ft_abs(vars->doors[i].center_y - ray_y) < vars->unit_size)
			return (i);
		i++;
	}
	return (-1);
}
