/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:45:13 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/01 18:57:25 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_door(t_vars *vars, int x, int y)
{
	return (vars->map->doors[y][x] != -1);
}

void	open_door(t_vars *vars, int x, int y)
{
	if (vars->map->doors[y][x] == DOOR_OPEN)
		vars->map->doors[y][x] = DOOR_CLOSED;
}

void	close_door(t_vars *vars, int x, int y)
{
	if (vars->map->doors[y][x] == DOOR_CLOSED)
		vars->map->doors[y][x] = DOOR_OPEN;
}

void	toggle_door(t_vars *vars, int x, int y)
{
	if (vars->map->doors[y][x] == DOOR_CLOSED)
		open_door(vars, x, y);
	else if (vars->map->doors[y][x] == DOOR_OPEN)
		close_door(vars, x, y);
}
