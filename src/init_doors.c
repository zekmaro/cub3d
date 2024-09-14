/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:35:24 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/14 20:06:34 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setup_door(t_vars *vars, t_door *door)
{
	door->x = door->grid_x * vars->unit_size;
	door->y = door->grid_y * vars->unit_size;
	door->center_x = door->x + vars->unit_size / 2;
	door->center_y = door->y + vars->unit_size / 2;
	door->state = 0;
	door->animation_progress = 0;
	get_current_time(&door->time0);
}

void	init_door(t_vars *vars, int i, int j, int *counter_doors)
{
	vars->door[*counter_doors].grid_x = j;
	vars->door[*counter_doors].grid_y = i;
	setup_door(vars, &vars->door[*counter_doors]);
	(*counter_doors)++;
}

void	init_doors(t_vars *vars)
{
	int	i;
	int	j;
	int	counter_doors;

	counter_doors = 0;
	i = -1;
	while (vars->map->grid[++i])
	{
		j = -1;
		while (vars->map->grid[i][++j])
		{
			if (vars->map->grid[i][j] == 'D')
				init_door(vars, i, j, &counter_doors);
		}
	}
	vars->map->num_doors = counter_doors;
}

void	printout_doors(t_vars *vars)
{
	int	i;

	printf("Number of doors: %d\n", vars->map->num_doors);
	i = 0;
	while (i < vars->map->num_doors)
	{
		printf("#%d: x: %d, y: %d, st: %d, anims: %f cntx: %d, cnty: %d\n", \
			i, vars->door[i].grid_x, vars->door[i].grid_y, \
			vars->door[i].state, vars->door[i].animation_progress, \
			vars->door[i].center_x, vars->door[i].center_y);
		i++;
	}
}
