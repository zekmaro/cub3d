/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/08/28 17:35:43 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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

void rotate_around_point(int *x, int *y, int cx, int cy, double angle)
{
    int temp_x = *x - cx;
    int temp_y = *y - cy;

    *x = temp_x * cos(angle) - temp_y * sin(angle) + cx;
    *y = temp_x * sin(angle) + temp_y * cos(angle) + cy;
}

void draw_player(t_vars *vars, int x, int y, unsigned int color, int unit_size)
{
    // Calculate the center of the square
    int cx = x + unit_size / 2;
    int cy = y + unit_size / 2;
	int i = 0;
	int j;

	i = 0;
    while (i < unit_size)
    {
		j = 0;
        while (j < unit_size)
        {
            // Calculate the original position of the pixel before rotation
            int px = x + j;
            int py = y + i;

            // Rotate the pixel around the center
            rotate_around_point(&px, &py, cx, cy, vars->map->angle);

            // Draw the pixel at the rotated position
            put_pixel_to_image(vars, px, py, color);
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
	player_size = 16;
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
	draw_player(vars, vars->player->x, vars->player->y, RED, player_size);
	//draw_ray(vars);
}
