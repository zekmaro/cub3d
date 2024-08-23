/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/08/23 16:44:33 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_vars *vars, int x, int y, unsigned int color, int unit_size)
{
	int i;
	int j;

	i = 0;
	while (i < unit_size)
	{
		j = 0;
		while (j < unit_size)
		{
			put_pixel_to_image(vars, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_vars *vars)
{
	int i;
	int j;
	int	unit_size;
	int player_size;

	i = 0;
	unit_size = 64;
	player_size = 10;
	while (i < vars->map->height)
	{
		j = 0;
		while (j < vars->map->width)
		{
			vars->line->x0 = j * unit_size;
			vars->line->y0 = i * unit_size;
			if (vars->map->grid[i][j] == '1')
			{
				draw_square(vars, vars->line->x0, vars->line->y0, PURPLE, unit_size);
			}
			else
			{
				draw_square(vars, vars->line->x0, vars->line->y0, WHITE, unit_size);
			}
			j++;
		}
		i++;
	}
	draw_square(vars, vars->player->x, vars->player->y, RED, 10);
}
