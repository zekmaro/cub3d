/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:15:16 by iberegsz          #+#    #+#             */
/*   Updated: 2024/08/29 21:17:56 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cast_ray(t_vars *vars, double ray_angle, int ray_id)
{
	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	distance_to_wall;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;

	ray_x = vars->player->x;
	ray_y = vars->player->y;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	distance_to_wall = 0;
	while (vars->map->grid[(int)(ray_y / vars->unit_size)] \
		[(int)(ray_x / vars->unit_size)] != '1')
	{
		ray_x += ray_dir_x;
		ray_y += ray_dir_y;
	}
	distance_to_wall = sqrt(pow(ray_x - vars->player->x, 2) \
		+ pow(ray_y - vars->player->y, 2));
	line_height = (int)(vars->mlx->window_height * 10 / distance_to_wall);
	draw_start = -line_height / 2 + vars->mlx->window_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + vars->mlx->window_height / 2;
	if (draw_end >= vars->mlx->window_height)
		draw_end = vars->mlx->window_height - 1;
	y = draw_start;
	while (y < draw_end)
	{
		put_pixel_to_image(vars, ray_id, y, WHITE);
		y++;
	}
}

void	raycast(t_vars *vars)
{
	int		x;
	double	fov;
	double	angle_step;
	double	start_angle;
	double	ray_angle;

	fov = M_PI / 3;
	angle_step = fov / vars->mlx->window_width;
	start_angle = vars->player->angle - (fov / 2);
	x = 0;
	while (x < vars->mlx->window_width)
	{
		ray_angle = start_angle + x * angle_step;
		cast_ray(vars, ray_angle, x);
		x++;
	}
}
