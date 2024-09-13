/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:17:29 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 03:03:07 by iberegsz         ###   ########.fr       */
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
		vars->minimap_update_y -= move_y;
		vars->minimap_update_x -= move_x;
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

void	update_ray_position(t_ray_par *ray)
{
	ray->dir_x += cos(ray->angle);
	ray->dir_y += sin(ray->angle);
}

int	check_collision(t_vars *vars, t_enemy *enemy, t_ray_par *ray)
{
	int	enemy_flag;

	enemy_flag = 0;
	while (!is_wall(vars, ray->dir_y, ray->dir_x) && !enemy_flag)
	{
		update_ray_position(ray);
		enemy_flag = is_enemy(enemy, ray->dir_y, ray->dir_x);
	}
	return (enemy_flag);
}

void	check_enemy_collision(t_vars *vars, t_enemy *enemy, int damage)
{
	t_ray_par	ray;
	int			enemy_flag;

	ray.x = vars->player->center_x;
	ray.y = vars->player->center_y;
	ray.dir_x = ray.x;
	ray.dir_y = ray.y;
	ray.angle = vars->player->angle;
	enemy_flag = check_collision(vars, enemy, &ray);
	if (enemy_flag)
	{
		system("aplay ./assets/imp_pain.wav -q &");
		enemy->health -= damage;
	}
	if (enemy->health == 0)
	{
		if (!vars->imp->is_dead)
			system("aplay ./assets/imp_death.wav -q &");
		enemy->current_animation = enemy->death;
		enemy->current_frame = 0;
		enemy->health -= 10;
	}
}
