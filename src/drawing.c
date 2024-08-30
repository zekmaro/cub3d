/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/08/29 21:42:11 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
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

void draw_player(t_vars *vars, unsigned int color)
{
	int i;
	int j;
	int pixel_x;
	int pixel_y;

	i = 0;
	vars->player->center_x = vars->player->x + vars->player->player_size / 2;
    vars->player->center_y = vars->player->y + vars->player->player_size / 2;
    while (i < vars->player->player_size)
    {
		j = 0;
        while (j < vars->player->player_size)
        {
            pixel_x = vars->player->x + j;
            pixel_y = vars->player->y + i;
            rotate_around_point(&pixel_x, &pixel_y, vars->player->center_x,
				vars->player->center_y, vars->player->angle);
            put_pixel_to_image(vars, pixel_x, pixel_y, color);
			j++;
        }
		i++;
    }
}

void	get_ray_target_coors(t_vars *vars, double move_y, double move_x)
{
	double x0;
	double y0;
	double x1;
	double y1;

	x0 = vars->player->center_x;
	y0 = vars->player->center_y;
	x1 = x0;
	y1 = y0;
	while (!is_wall(vars, y1, x1))
	{
		y1 += move_y;
		x1 += move_x;
		put_pixel_to_image(vars, x1, y1, GREEN);
	}
}

void	draw_ray(t_vars *vars)
{
	get_ray_target_coors(vars, -tan(vars->player->fov / 2), 1);
	get_ray_target_coors(vars, tan(vars->player->fov / 2), 1);
}

void	draw_floor(t_vars *vars)
{
	int i;
	int j;

	i = vars->mlx->window_height / 2;
	while (i < vars->mlx->window_height)
	{
		j = 0;
		while (j < vars->mlx->window_width)
		{
			put_pixel_to_image(vars, j, i, BROWN);
			j++;
		}
		i++;
	}
}

void	draw_ceiling(t_vars *vars)
{
	int i;
	int j;

	i = vars->mlx->window_height / 2;
	while (i > 0)
	{
		j = 0;
		while (j < vars->mlx->window_width)
		{
			put_pixel_to_image(vars, j, i, LIGHT_BLUE);
			j++;
		}
		i--;
	}
}

void	draw_map(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	draw_floor(vars);
	draw_ceiling(vars);
	while (i < vars->map->height)
	{
		j = 0;
		while (j < vars->map->width)
		{
			vars->line->x0 = j * vars->unit_size;
			vars->line->y0 = i * vars->unit_size;
			if (vars->map->grid[i][j] == '1')
			{
				draw_square(vars, vars->line->x0, vars->line->y0, PURPLE, vars->unit_size);
			}
			else
			{
				draw_square(vars, vars->line->x0, vars->line->y0, WHITE, vars->unit_size);
			}
			j++;
		}
		i++;
	}
	draw_player(vars, RED);
	draw_ray(vars);
	raycast(vars);
}
