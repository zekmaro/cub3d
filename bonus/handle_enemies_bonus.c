/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemies_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:40:14 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/24 16:59:00 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	enemy_shoot(t_enemy *enemy, int vector_x, int vector_y, int vector)
{
	if (enemy->health > 0 && enemy->current_animation != enemy->death)
	{
		enemy->current_animation = enemy->attack;
		enemy->current_frame = 0;
	}
	enemy->fire_delta_y = (vector_y * vector_y / vector) / 10;
	if (vector_y < 0)
		enemy->fire_delta_y *= -1;
	enemy->fire_delta_x = (vector_x * vector_x / vector) / 10;
	if (vector_x < 0)
		enemy->fire_delta_x *= -1;
	enemy->shoot_ball = 1;
}

void	enemy_act(t_vars *vars, t_enemy *enemy)
{
	int	vector_x;
	int	vector_y;
	int	vector;

	vector_x = vars->player->center_x - enemy->center_x;
	vector_y = vars->player->center_y - enemy->center_y;
	vector = sqrt(vector_x * vector_x + vector_y * vector_y);
	if (!is_wall(vars, enemy->center_y + vector_y / 40,
			enemy->center_x + vector_x / 40))
	{
		enemy->center_x += vector_x / 40;
		enemy->center_y += vector_y / 40;
	}
	if (!enemy->shoot_ball)
		enemy_shoot(enemy, vector_x, vector_y, vector);
	if (is_wall(vars, enemy->fire_ball_y, enemy->fire_ball_x) \
		|| is_closed_door(vars, enemy->fire_ball_y, enemy->fire_ball_x))
	{
		enemy->fire_ball_y = enemy->center_y;
		enemy->fire_ball_x = enemy->center_x;
		enemy->shoot_ball = 0;
	}
	else
		handle_enemy_shot(vars, enemy);
	enemy->detected_player = 0;
}

void	search_for_player(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->map->imp_list_size)
		if (!vars->imp_list[i].detected_player)
			vars->imp_list[i].angle += M_PI / 10 * vars->imp_list[i].rot_dir;
	i = -1;
	while (++i < vars->map->caco_list_size)
		if (!vars->caco_list[i].detected_player)
			vars->caco_list[i].angle += M_PI / 10 * vars->caco_list[i].rot_dir;
	if (!vars->boss->detected_player)
		vars->boss->angle += M_PI / 10 * vars->boss->rot_dir;
}

void	act_detected_enemies(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->map->imp_list_size)
		if (vars->imp_list[i].detected_player)
			enemy_act(vars, &vars->imp_list[i]);
	i = -1;
	while (++i < vars->map->caco_list_size)
		if (vars->caco_list[i].detected_player)
			enemy_act(vars, &vars->caco_list[i]);
	if (vars->boss->detected_player)
		enemy_act(vars, vars->boss);
}

long	update_imp_time(t_vars *vars)
{
	long	elapsed_time;

	get_current_time(&vars->imp->time1);
	elapsed_time = get_elapsed_time(&vars->imp->time0, &vars->imp->time1);
	return (elapsed_time);
}
