/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:40:10 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/29 21:16:32 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void print_map(t_map *map)
{
    int i;

    if (!map || !map->grid)
        return;

    i = 0;
    while (i < map->height)
    {
        ft_putstr_fd(map->grid[i], 1);
        i++;
    }
	ft_putchar_fd('\n', 1);
}

int	is_wall(t_vars *vars, int y, int x)
{
	return (vars->map->grid[y / vars->unit_size][x / vars->unit_size] == '1');
}

int	player_inside_map(t_vars *vars, int x, int y)
{
	return (x < vars->map->width
		&& y < vars->map->height);
}

int	can_move(t_vars *vars, int y, int x)
{
	if (player_inside_map(vars, x, y))
	{
		if (vars->map->grid[y][x] == '1')
			return (0);
		return (1);
	}
	else
		return (0);
}
