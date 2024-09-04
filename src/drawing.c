/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/09/01 02:01:00 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_vars *vars, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->unit_size)
	{
		j = 0;
		while (j < vars->unit_size)
		{
			put_pixel_to_image(vars, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	rotate_around_point(t_vars *vars, int *x, int *y)
{
	int		temp_x;
	int		temp_y;
	double	angle;
	int		cx;
	int		cy;

	angle = vars->player->angle;
	cx = vars->player->center_x;
	cy = vars->player->center_y;
	temp_x = *x - cx;
	temp_y = *y - cy;
	*x = temp_x * cos(angle) - temp_y * sin(angle) + cx;
	*y = temp_x * sin(angle) + temp_y * cos(angle) + cy;
}

void	update_player_position(t_vars *vars)
{
	vars->player->center_x = vars->player->x + vars->player->player_size / 2;
	vars->player->center_y = vars->player->y + vars->player->player_size / 2;
}

void	draw_player(t_vars *vars, unsigned int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	i = 0;
	update_player_position(vars);
	while (i < vars->player->player_size)
	{
		j = 0;
		while (j < vars->player->player_size)
		{
			pixel_x = vars->player->x + j;
			pixel_y = vars->player->y + i;
			rotate_around_point(vars, &pixel_x, &pixel_y);
			put_pixel_to_image(vars, pixel_x, pixel_y, color);
			j++;
		}
		i++;
	}
}

void	draw_ray(t_vars *vars, double angle_offset)
{
	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_angle;

	ray_angle = vars->player->angle + angle_offset;
	ray_x = vars->player->center_x;
	ray_y = vars->player->center_y;
	ray_dir_x = ray_x;
	ray_dir_y = ray_y;
	while (!is_wall(vars, ray_dir_y, ray_dir_x))
	{
		ray_dir_x += cos(ray_angle);
		ray_dir_y += sin(ray_angle);
		put_pixel_to_image(vars, (int)ray_dir_x, (int)ray_dir_y, GREEN);
	}
}

void	draw_ray_segment(t_vars *vars)
{
	double	fov_half;
	double	radian;

	fov_half = vars->player->fov / 2;
	radian = 0;
	while (radian < vars->player->fov)
	{
		draw_ray(vars, -fov_half + radian);
		radian += 0.01;
	}
}

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
			else if (vars->map->grid[i][j] == 'M')
				draw_square(vars, vars->line->x0, vars->line->y0, BLUE);
			else
				draw_square(vars, vars->line->x0, vars->line->y0, WHITE);
			j++;
		}
		i++;
	}
	draw_player(vars, RED);
}

// void	handle_sprites(t_vars *vars)
// {

// }

void	draw_map(t_vars *vars)
{
	draw_floor(vars);
	draw_ceiling(vars);
	// draw_minimap(vars);
	// draw_ray_segment(vars);
	raycast(vars);
	//handle_sprites(vars);
	update_player_position(vars);
}
