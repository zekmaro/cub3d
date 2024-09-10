/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:40:14 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/10 14:41:17 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_enemy_list(t_enemy *enemy_list, long delay, int size)
{
	long	enemy_elapsed_time;
	int		i;

	i = -1;
	while (++i < size)
	{
		get_current_time(&enemy_list[i].time1);
		enemy_elapsed_time = get_elapsed_time(&enemy_list[i].time0, \
			&enemy_list[i].time1);
		if (enemy_elapsed_time > delay)
		{
			if (enemy_list[i].current_animation == enemy_list[i].death_animation
				&& enemy_list[i].current_animation->current_frame
				== enemy_list[i].current_animation->frame_count - 1)
			{
				enemy_list[i].is_dead = 1;
				enemy_list[i].center_x = -100;
				enemy_list[i].center_y = -100;
			}
			update_sprite_frame(enemy_list[i].current_animation);
			if (enemy_list[i].current_animation \
				== enemy_list[i].attack_animation
				&& enemy_list[i].current_animation->current_frame \
				== enemy_list[i].current_animation->frame_count - 1)
				enemy_list[i].current_animation = enemy_list[i].move_animation;
			enemy_list[i].time0 = enemy_list[i].time1;
		}
	}
}

void	enemy_shoot(t_enemy *enemy, int vector_x, int vector_y, int vector)
{
	if (enemy->health > 0)
		enemy->current_animation = enemy->attack_animation;
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
	enemy->center_x += vector_x / 40;
	enemy->center_y += vector_y / 40;
	if (!enemy->shoot_ball)
		enemy_shoot(enemy, vector_x, vector_y, vector);
	if (is_wall(vars, enemy->fire_ball_y, enemy->fire_ball_x))
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
}
