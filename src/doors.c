/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:45:13 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/14 15:16:49 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	check_player_proximity_to_doors(t_vars *vars)
// {
//     int		i;
//     double	distance;
//     double	player_x = vars->player->x;
//     double	player_y = vars->player->y;

// 	i = 0;
// 	while (i < vars->map->num_doors)
// 	{
// 		t_door *door = &vars->map->doors[i];
// 		distance = sqrt(pow(player_x - door->center_x, 2)
//			+ pow(player_y - door->center_y, 2));
// 		if (distance < DOOR_PROXIMITY_THRESHOLD)
// 		{
// 			open_door(vars, door->x, door->y);
// 		}
// 		i++;
// 	}
// }

void	open_door(t_vars *vars, int x, int y)
{
	if (is_door(vars, x, y))
		vars->map->grid[y][x] = '0';
}

void	close_door(t_vars *vars, int x, int y)
{
	if (is_door(vars, x, y))
		vars->map->grid[y][x] = 'D';
}

// int	is_door(t_vars *vars, int x, int y)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < vars->map->num_doors)
// 		if (vars->map->doors[i].x == x && vars->map->doors[i].y == y)
// 			return (1);
// 	return (0);
// }

// int	set_door(t_vars *vars, int x, int y)
// {
// 	if (is_door(vars, x, y))
// 		return (0);
// 	if (vars->map->num_doors >= MAX_DOORS)
// 	{
// 		printf("Too many doors in the map\n");
// 		return (0);
// 	}
// 	vars->map->doors[vars->map->num_doors].x = x;
// 	vars->map->doors[vars->map->num_doors].y = y;
// 	vars->map->doors[vars->map->num_doors].state = DOOR_CLOSED;
// 	vars->map->doors[vars->map->num_doors].animation_progress = 0.0;
// 	vars->map->num_doors++;
// 	return (1);
// }

// int	get_door_index(t_vars *vars, int x, int y)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < vars->map->num_doors)
// 		if (vars->map->doors[i].x == x && vars->map->doors[i].y == y)
// 			return (i);
// 	return (-1);
// }

// int	get_door_state(t_vars *vars, int x, int y)
// {
// 	if (is_door(vars, x, y))
// 		return (vars->map->doors[get_door_index(vars, x, y)].state);
// 	return (DOOR_NONE);
// }

// void	toggle_door(t_vars *vars, int x, int y)
// {
// 	if (get_door_state(vars, x, y) == DOOR_CLOSED)
// 		open_door(vars, x, y);
// 	else if (get_door_state(vars, x, y) == DOOR_OPEN)
// 		close_door(vars, x, y);
// }
