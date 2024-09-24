/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_construction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:42:14 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/12 13:43:28 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall(t_vars *vars, int y, int x)
{
	return (vars->map->grid[y / vars->unit_size][x \
		/ vars->unit_size] == '1');
}

int	is_door(t_vars *vars, int y, int x)
{
	return (vars->map->grid[y / vars->unit_size][x \
		/ vars->unit_size] == 'D');
}
