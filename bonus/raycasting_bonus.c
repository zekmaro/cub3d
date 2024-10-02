/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:15:16 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/30 03:35:28 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setup_ray(t_vars *vars, double ray_x, double ray_y)
{
	vars->ray->distance_to_wall = sqrt(pow(ray_x \
		- vars->player->x, 2) + pow(ray_y - vars->player->y, 2));
	vars->ray->distance_to_wall *= cos(vars->player->angle \
		- vars->ray->ray_angle);
	if (vars->ray->distance_to_wall < 10)
		vars->ray->distance_to_wall = 10;
	vars->ray->line_height = (int)(vars->mlx->window_height \
		* vars->unit_size / vars->ray->distance_to_wall);
	vars->ray->draw_start = -vars->ray->line_height / 2 \
		+ vars->mlx->window_height / 2;
	vars->ray->draw_end = vars->ray->line_height / 2 \
		+ vars->mlx->window_height / 2;
	if (vars->ray->draw_end >= vars->mlx->window_height)
		vars->ray->draw_end = vars->mlx->window_height - 1;
}

void	draw_ray_column(t_vars *vars, int ray_id, t_tex_typ texture_index)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;
	int	temp;

	temp = 0;
	y = vars->ray->draw_start;
	while (temp++ < y)
		put_pixel_to_image(vars, ray_id, temp, vars->ceiling_color);
	while (y < vars->ray->draw_end)
	{
		get_texture_coords(vars, texture_index, &tex_x);
		tex_y = (int)((y - vars->ray->draw_start) \
			* vars->unit_size / vars->ray->line_height);
		if (texture_index == TEXTURE_SOUTH)
			tex_y += 1;
		texture_index %= 8;
		color = get_texture_color(vars, vars->textures[texture_index], tex_x, tex_y);
		put_pixel_to_image(vars, ray_id, y, color);
		y++;
	}
	while (y++ < vars->mlx->window_height)
		put_pixel_to_image(vars, ray_id, y, vars->floor_color);
}

static void	cast_ray(t_vars *vars, int ray_id)
{
	t_tex_typ	texture_index;

	get_ray_target_coords(vars);
	setup_ray(vars, vars->ray->ray_x, vars->ray->ray_y);
	texture_index = define_texture_type(vars);
	draw_ray_column(vars, ray_id, texture_index);
	vars->zbuffer[ray_id] = vars->ray->distance_to_wall;
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
