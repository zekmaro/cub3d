/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:45:13 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/07 18:20:29 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_door(t_vars *vars, int x, int y)
{
	return (vars->map->doors[y][x].state != DOOR_NONE);
}

void	open_door(t_vars *vars, int x, int y)
{
	if (vars->map->doors[y][x].state == DOOR_OPEN)
		vars->map->doors[y][x].state = DOOR_CLOSED;
}

void	close_door(t_vars *vars, int x, int y)
{
	if (vars->map->doors[y][x].state == DOOR_CLOSED)
		vars->map->doors[y][x].state = DOOR_OPEN;
}

void	toggle_door(t_vars *vars, int x, int y)
{
	if (vars->map->doors[y][x].state == DOOR_CLOSED)
		open_door(vars, x, y);
	else if (vars->map->doors[y][x].state == DOOR_OPEN)
		close_door(vars, x, y);
}
