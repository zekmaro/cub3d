/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:37:12 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/02 11:43:02 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_floor(t_vars *vars)
{
	int	i;
	int	j;

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
	int	i;
	int	j;

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
	draw_floor(vars);
	draw_ceiling(vars);
	raycast(vars);
	draw_minimap(vars);
	draw_ray_segment(vars);
}

void	draw_minimap(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map->height)
	{
		j = 0;
		while (j < vars->map->width)
		{
			vars->line->x0 = j * vars->unit_size;
			vars->line->y0 = i * vars->unit_size;
			if (vars->map->grid[i][j] == '1')
				draw_square(vars, vars->line->x0, vars->line->y0, BEIGE);
			else
				draw_square(vars, vars->line->x0, vars->line->y0, WHITE);
			j++;
		}
		i++;
	}
	draw_player(vars, RED);
}
