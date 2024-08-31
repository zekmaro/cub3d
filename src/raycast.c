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

void	get_ray_target_coors(t_vars *vars)
{
	vars->ray->ray_x = vars->player->x;
	vars->ray->ray_y = vars->player->y;
	vars->ray->ray_dir_x = cos(vars->ray->ray_angle);
	vars->ray->ray_dir_y = sin(vars->ray->ray_angle);
	while (!is_wall(vars, vars->ray->ray_y, vars->ray->ray_x))
	{
		vars->ray->ray_x += vars->ray->ray_dir_x;
		vars->ray->ray_y += vars->ray->ray_dir_y;
	}
}

void	setup_ray(t_vars *vars)
{
	vars->ray->distance_to_wall = sqrt(pow(vars->ray->ray_x - vars->player->x, 2) \
		+ pow(vars->ray->ray_y - vars->player->y, 2));
	vars->ray->line_height = (int)(vars->mlx->window_height * 20 / vars->ray->distance_to_wall);
	vars->ray->draw_start = -vars->ray->line_height / 2 + vars->mlx->window_height / 2;
	if (vars->ray->draw_start < 0)
		vars->ray->draw_start = 0;
	vars->ray->draw_end = vars->ray->line_height / 2 + vars->mlx->window_height / 2;
	if (vars->ray->draw_end >= vars->mlx->window_height)
		vars->ray->draw_end = vars->mlx->window_height - 1;
}

void	cast_ray(t_vars *vars, int ray_id)
{
	int		y;
	int		texture_index;
	int		tex_x;
	int		tex_y;
	int		color;

	get_ray_target_coors(vars);
	vars->ray->distance_to_wall = sqrt(pow(vars->ray->ray_x - vars->player->x, 2) \
		+ pow(vars->ray->ray_y - vars->player->y, 2));
	vars->ray->line_height = (int)(vars->mlx->window_height * 20 / vars->ray->distance_to_wall);
	vars->ray->draw_start = -vars->ray->line_height / 2 + vars->mlx->window_height / 2;
	if (vars->ray->draw_start < 0)
		vars->ray->draw_start = 0;
	vars->ray->draw_end = vars->ray->line_height / 2 + vars->mlx->window_height / 2;
	if (vars->ray->draw_end >= vars->mlx->window_height)
		vars->ray->draw_end = vars->mlx->window_height - 1;
	if (fabs(vars->ray->ray_dir_x) > fabs(vars->ray->ray_dir_y))
	{
		if (vars->ray->ray_dir_x > 0)
			texture_index = 2;
		else
			texture_index = 3;
	}
	else
	{
		if (vars->ray->ray_dir_y > 0)
			texture_index = 1;
		else
			texture_index = 0;
	}
	y = vars->ray->draw_start;
	while (y < vars->ray->draw_end)
	{
		tex_x = (int)(vars->ray->ray_x) % vars->unit_size;
		tex_y = (int)((y - vars->ray->draw_start) * vars->unit_size / vars->ray->line_height);
		color = get_texture_color(vars->textures[texture_index], tex_x, tex_y);
		put_pixel_to_image(vars, ray_id, y, color);
		y++;
	}
}

void	raycast(t_vars *vars)
{
	int		x;
	double	angle_step;
	double	start_angle;

	angle_step = vars->player->fov / vars->mlx->window_width;
	start_angle = vars->player->angle - (vars->player->fov / 2);
	x = 0;
	while (x < vars->mlx->window_width)
	{
		vars->ray->ray_angle = start_angle + x * angle_step;
		cast_ray(vars, x);
		x++;
	}
}
