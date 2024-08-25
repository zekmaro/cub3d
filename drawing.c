/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/08/25 15:30:07 by andrejarama      ###   ########.fr       */
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

int	is_wall(t_vars *vars, int y, int x)
{
	return (vars->map->grid[y / 64][x / 64] == '1');
}

void	get_ray_target_coors(t_vars *vars, int move_y, int move_x)
{
	int x;
	int y;
	int player_center_x;
	int player_center_y;

	player_center_x = vars->player->x + (8 / 2);
	player_center_y = vars->player->y + (8 / 2);
	x = (player_center_x + move_x);
	y = (player_center_y + move_y);
	vars->line->x0 = x;
	vars->line->y0 = y;
	vars->line->x1 = x;
	vars->line->y1 = y;
	while (!is_wall(vars, vars->line->y1, vars->line->x1))
	{
		vars->line->y1 += move_y;
		vars->line->x1 += move_x;
	}
}

void	draw_ray(t_vars *vars)
{
	get_ray_target_coors(vars, -8, -2);
	draw_line(vars, GREEN);
	get_ray_target_coors(vars, -8, 2);
	draw_line(vars, GREEN);
}

void	draw_map(t_vars *vars)
{
	int i;
	int j;
	int	unit_size;
	int player_size;

	i = 0;
	unit_size = 64;
	player_size = 8;
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
	draw_square(vars, vars->player->x, vars->player->y, RED, player_size);
	draw_ray(vars);
}
