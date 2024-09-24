/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:38:58 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/24 16:59:23 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	reset_mouse_to_center(t_vars *vars)
{
	int	center_x;
	int	center_y;

	center_x = vars->mlx->window_width / 2;
	center_y = vars->mlx->window_height / 2;
	mlx_mouse_move(vars->mlx->mlx, vars->mlx->win, center_x, center_y);
}

int	mouse_move(int x, int y, t_vars *vars)
{
	int		center_x;
	int		dx;
	double	rot_speed;

	(void)y;
	center_x = vars->mlx->window_width / 2;
	dx = x - center_x;
	rot_speed = 0.0002;
	vars->player->angle += dx * rot_speed;
	return (0);
}

int	shoot_entity(int button, int x, int y, t_vars *vars)
{
	int	i;

	(void)x;
	(void)y;
	if (button == MOUSE_CLICK_LEFT && !vars->player->shoot)
	{
		vars->player->shoot = 1;
		vars->player->fire_done = 0;
		i = -1;
		while (++i < vars->map->imp_list_size)
		{
			if (!vars->imp_list[i].is_dead)
				check_enemy_collision(vars, &vars->imp_list[i], 50);
		}
		i = -1;
		while (++i < vars->map->caco_list_size)
		{
			if (!vars->caco_list[i].is_dead)
				check_enemy_collision(vars, &vars->caco_list[i], 20);
		}
		check_enemy_collision(vars, vars->boss, 20);
	}
	return (0);
}
