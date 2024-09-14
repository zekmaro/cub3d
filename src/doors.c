/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:45:13 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/14 22:50:38 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
