/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:17:29 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/10 14:17:37 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player(t_vars *vars, int move_y, int move_x)
{
	int	x;
	int	y;
	int	save_x;
	int	save_y;

	x = vars->player->center_x + move_x * 5;
	y = vars->player->center_y + move_y * 5;
	save_x = x;
	save_y = y;
	rotate_around_point(vars, &x, &y);
	if (can_move(vars, save_y / vars->unit_size, save_x / vars->unit_size))
	{
		vars->player->y += move_y;
		vars->player->x += move_x;
	}
}

void	update_position(t_vars *vars)
{
	int	move_x;
	int	move_y;

	move_x = 8;
	move_y = 8;
	if (vars->keys.w == 1)
		move_player(vars, move_y * sin(vars->player->angle), \
			move_x * cos(vars->player->angle));
	if (vars->keys.s == 1)
		move_player(vars, -move_y * sin(vars->player->angle), \
			-move_x * cos(vars->player->angle));
	if (vars->keys.d == 1)
		move_player(vars, move_y * cos(vars->player->angle), \
			-move_x * sin(vars->player->angle));
	if (vars->keys.a == 1)
		move_player(vars, -move_y * cos(vars->player->angle), \
			move_x * sin(vars->player->angle));
	if (vars->keys.left == 1)
		vars->player->angle -= M_PI / 45;
	if (vars->keys.right == 1)
		vars->player->angle += M_PI / 45;
}

void	check_enemy_collision(t_vars *vars, t_enemy *enemy, int damage)
{
	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_angle;
	int		enemy_flag;

	ray_angle = vars->player->angle;
	ray_x = vars->player->center_x;
	ray_y = vars->player->center_y;
	ray_dir_x = ray_x;
	ray_dir_y = ray_y;
	enemy_flag = 0;
	while (!is_wall(vars, ray_dir_y, ray_dir_x) && !enemy_flag)
	{
		ray_dir_x += cos(ray_angle);
		ray_dir_y += sin(ray_angle);
		enemy_flag = is_enemy(enemy, ray_dir_y, ray_dir_x);
	}
	if (enemy_flag)
	{
		//system("aplay ./assets/imp_pain.wav -q &");
		enemy->health -= damage;
	}
	if (enemy->health == 0)
	{
		// if (!vars->imp->is_dead)
		// 	system("aplay ./assets/imp_death.wav -q &");
		enemy->current_animation = enemy->death_animation;
	}
}
