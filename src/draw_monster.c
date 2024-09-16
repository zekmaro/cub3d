/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_monster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:18:43 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/16 12:22:47 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_monster(t_vars *vars, unsigned int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			pixel_x = vars->imp->center_x - 4 + j;
			pixel_y = vars->imp->center_y - 4 + i;
			put_pixel_to_image(vars, pixel_x, pixel_y, color);
		}
	}
}

void	cast_ray_enemy(t_vars *vars, t_enemy *enemy, double angle_offset)
{
	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_angle;

	ray_angle = enemy->angle + angle_offset;
	ray_x = enemy->center_x;
	ray_y = enemy->center_y;
	ray_dir_x = ray_x;
	ray_dir_y = ray_y;
	while (!is_wall(vars, ray_dir_y, ray_dir_x)
		&& !is_closed_door(vars, ray_dir_y, ray_dir_x))
	{
		ray_dir_x += cos(ray_angle);
		ray_dir_y += sin(ray_angle);
		if (!enemy->detected_player)
		{
			enemy->detected_player = is_player(vars, ray_dir_y, ray_dir_x);
			if (enemy->detected_player && angle_offset > 0.00)
				enemy->rot_dir = 1;
			else if (enemy->detected_player && angle_offset < 0.00)
				enemy->rot_dir = -1;
		}
	}
}

void	search_for_player_enemy(t_vars *vars, t_enemy *enemy)
{
	double	fov_half;
	double	radian;

	fov_half = vars->player->fov / 2;
	radian = 0;
	enemy->detected_player = 0;
	while (radian < vars->player->fov)
	{
		cast_ray_enemy(vars, enemy, -fov_half + radian);
		radian += 0.01;
	}
}
// Comment from cast_ray_enemy
// ray_dir_x += cos(ray_angle);
// ray_dir_y += sin(ray_angle);
// //put_pixel_to_image(vars, (int)ray_dir_x, (int)ray_dir_y, BLUE);
// if (!enemy->detected_player)
