/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:02:48 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 01:03:05 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_imp(t_vars *vars, int i, int j, int *counter_imp)
{
	vars->imp_list[*counter_imp].grid_x = j;
	vars->imp_list[*counter_imp].grid_y = i;
	setup_imp(vars, &vars->imp_list[*counter_imp]);
	(*counter_imp)++;
}

void	init_caco(t_vars *vars, int i, int j, int *counter_caco)
{
	vars->caco_list[*counter_caco].grid_x = j;
	vars->caco_list[*counter_caco].grid_y = i;
	setup_caco(vars, &vars->caco_list[*counter_caco]);
	(*counter_caco)++;
}

void	init_enemies(t_vars *vars)
{
	int	i;
	int	j;
	int	counter_imp;
	int	counter_caco;

	counter_imp = 0;
	counter_caco = 0;
	i = -1;
	while (vars->map->grid[++i])
	{
		j = -1;
		while (vars->map->grid[i][++j])
		{
			if (vars->map->grid[i][j] == 'M')
				init_imp(vars, i, j, &counter_imp);
			else if (vars->map->grid[i][j] == 'C')
				init_caco(vars, i, j, &counter_caco);
		}
	}
}
