/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:15:16 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/02 12:30:59 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_ray_target_coords(t_vars *vars)
{
	vars->ray->ray_x = vars->player->x;
	vars->ray->ray_y = vars->player->y;
	vars->ray->ray_dir_x = cos(vars->ray->ray_angle);
	vars->ray->ray_dir_y = sin(vars->ray->ray_angle);
	while (!is_wall(vars, vars->ray->ray_y, vars->ray->ray_x))
	{
		vars->ray->last_ray_x = vars->ray->ray_x;
		vars->ray->last_ray_y = vars->ray->ray_y;
		vars->ray->ray_x += vars->ray->ray_dir_x;
		vars->ray->ray_y += vars->ray->ray_dir_y;
	}
}

void	setup_ray(t_vars *vars)
{
	vars->ray->distance_to_wall = sqrt(pow(vars->ray->ray_x \
		- vars->player->x, 2) + pow(vars->ray->ray_y - vars->player->y, 2));
	vars->ray->line_height = (int)(vars->mlx->window_height \
		* vars->unit_size / 2 / vars->ray->distance_to_wall);
	vars->ray->draw_start = -vars->ray->line_height / 2 \
		+ vars->mlx->window_height / 2;
	if (vars->ray->draw_start < 0)
		vars->ray->draw_start = 0;
	vars->ray->draw_end = vars->ray->line_height / 2 \
		+ vars->mlx->window_height / 2;
	if (vars->ray->draw_end >= vars->mlx->window_height)
		vars->ray->draw_end = vars->mlx->window_height - 1;
}

t_tex_typ	define_texture_type(t_vars *vars)
{
	int			dx;
	int			dy;
	t_tex_typ	texture_type;

	texture_type = 0;
	dx = (int)vars->ray->last_ray_x / vars->unit_size \
		- (int)vars->ray->ray_x / vars->unit_size;
	dy = (int)vars->ray->last_ray_y / vars->unit_size \
		- (int)vars->ray->ray_y / vars->unit_size;
	if (dy == 1)
		texture_type = TEXTURE_NORTH;
	else if (dy == -1)
		texture_type = TEXTURE_SOUTH;
	else if (dx == 1)
		texture_type = TEXTURE_WEST;
	else if (dx == -1)
		texture_type = TEXTURE_EAST;
	return (texture_type);
}

void	cast_ray(t_vars *vars, int ray_id)
{
	t_tex_typ	texture_index;

	get_ray_target_coords(vars);
	setup_ray(vars);
	texture_index = define_texture_type(vars);
	draw_ray_column(vars, ray_id, texture_index);
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
