/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:04:43 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/16 11:49:20 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_object(t_vars *vars, int y, int x)
{
	int	i;

	i = 0;
	while (i < vars->map->imp_list_size)
	{
		if (is_enemy(&vars->imp_list[i], y, x))
		{
			vars->imp_list[i].draw = 1;
		}
		i++;
	}
	i = 0;
	while (i < vars->map->caco_list_size)
	{
		if (is_enemy(&vars->caco_list[i], y, x))
		{
			vars->caco_list[i].draw = 1;
		}
		i++;
	}
	if (is_enemy(vars->boss, y, x))
	{
		vars->boss->draw = 1;
	}
}

static void	search_for_objects(t_vars *vars, double angle_offset)
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
		check_object(vars, ray_dir_y, ray_dir_x);
	}
}

void	check_objects_to_draw(t_vars *vars)
{
	double	fov_half;
	double	radian;

	fov_half = vars->player->fov / 2;
	radian = 0;
	while (radian < vars->player->fov)
	{
		search_for_objects(vars, -fov_half + radian);
		radian += 0.01;
	}
}
