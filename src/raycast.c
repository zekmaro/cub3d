/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:15:16 by iberegsz          #+#    #+#             */
/*   Updated: 2024/08/31 16:57:56 by iberegsz         ###   ########.fr       */
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
	int		texture_index;
	int		tex_x;
	int		tex_y;
	int		color;

	ray_x = vars->player->x;
	ray_y = vars->player->y;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	while (vars->map->grid[(int)(ray_y / vars->unit_size)] \
		[(int)(ray_x / vars->unit_size)] != '1')
	{
		ray_x += ray_dir_x;
		ray_y += ray_dir_y;
	}
	distance_to_wall = sqrt(pow(ray_x - vars->player->x, 2) \
		+ pow(ray_y - vars->player->y, 2));
	line_height = (int)(vars->mlx->window_height * 20 / distance_to_wall);
	draw_start = -line_height / 2 + vars->mlx->window_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + vars->mlx->window_height / 2;
	if (draw_end >= vars->mlx->window_height)
		draw_end = vars->mlx->window_height - 1;
	if (fabs(ray_dir_x) > fabs(ray_dir_y))
	{
		if (ray_dir_x > 0)
			texture_index = 2;
		else
			texture_index = 3;
	}
	else
	{
		if (ray_dir_y > 0)
			texture_index = 1;
		else
			texture_index = 0;
	}
	y = draw_start;
	while (y < draw_end)
	{
		tex_x = (int)(ray_x) % vars->unit_size;
		tex_y = (int)((y - draw_start) * vars->unit_size / line_height);
		color = get_texture_color(vars->textures[texture_index], tex_x, tex_y);
		put_pixel_to_image(vars, ray_id, y, color);
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
