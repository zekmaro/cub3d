/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:15:16 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/03 22:52:51 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	setup_ray(t_vars *vars, double ray_x, double ray_y)
{
	vars->ray->distance_to_wall = sqrt(pow(ray_x \
		- vars->player->x, 2) + pow(ray_y - vars->player->y, 2));
	vars->ray->distance_to_wall *= cos(vars->player->angle \
		- vars->ray->ray_angle);
	vars->ray->line_height = (int)(vars->mlx->window_height \
		* vars->unit_size / vars->ray->distance_to_wall);
	vars->ray->draw_start = -vars->ray->line_height / 2 \
		+ vars->mlx->window_height / 2;
	if (vars->ray->draw_start < 0)
		vars->ray->draw_start = 0;
	vars->ray->draw_end = vars->ray->line_height / 2 \
		+ vars->mlx->window_height / 2;
	if (vars->ray->draw_end >= vars->mlx->window_height)
		vars->ray->draw_end = vars->mlx->window_height - 1;
}

void	get_texture_coords(t_vars *vars, t_tex_typ texture_index, int *tex_x)
{
	if (texture_index % 2 == 0)
	{
		*tex_x = (int)(vars->ray->ray_x) % vars->unit_size;
		if (texture_index == TEXTURE_SOUTH)
		{
			*tex_x *= -1; 
			*tex_x -= 1;
		}
	}
	else if (texture_index % 2 == 1)
	{
		*tex_x = (int)(vars->ray->ray_y) % vars->unit_size;
		if (texture_index == TEXTURE_WEST)
		{
			*tex_x = vars->unit_size - *tex_x;
			*tex_x -= 1;
		}
	}
}

int	get_map_x(t_vars *vars)
{
	return ((int)(vars->ray->ray_x / vars->unit_size));
}

int	get_map_y(t_vars *vars)
{
	return ((int)(vars->ray->ray_y / vars->unit_size));
}

void	draw_ray_column(t_vars *vars, int ray_id, t_tex_typ texture_index)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;
	int temp = 0;

	(void)ray_id;
	y = vars->ray->draw_start;
	while (temp++ < y)
		put_pixel_to_image(vars, ray_id, temp, LIGHT_BLUE);
	while (y < vars->ray->draw_end)
	{
		get_texture_coords(vars, texture_index, &tex_x);
		tex_y = (int)((y - vars->ray->draw_start) * vars->unit_size \
			/ vars->ray->line_height);
		if (texture_index == TEXTURE_SOUTH)
			tex_y += 1;
		color = get_texture_color(vars->textures[texture_index], tex_x, tex_y);
		put_pixel_to_image(vars, ray_id, y, color);
		y++;
	}
	while (y++ < vars->mlx->window_height)
		put_pixel_to_image(vars, ray_id, y, BROWN);
}

void	cast_ray(t_vars *vars, int ray_id)
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
