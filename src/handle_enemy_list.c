/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:46:23 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 02:52:39 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_enemy_lists(t_vars *vars)
{
	vars->imp_list = ft_calloc(sizeof(t_enemy), vars->map->imp_list_size);
	if (!vars->imp_list)
	{
		exit_with_error(vars, "Failed to allocate memory for imp list");
		exit(EXIT_FAILURE);
	}
	vars->caco_list = ft_calloc(sizeof(t_enemy), vars->map->caco_list_size);
	if (!vars->caco_list)
	{
		exit_with_error(vars, "Failed to allocate memory for caco list");
		exit(EXIT_FAILURE);
	}
}

void	update_sprite_frame_enemy(t_enemy *enemy)
{
	enemy->current_frame = (enemy->current_frame + 1) \
		% enemy->current_animation->frame_count;
}

void	update_enemy_frames(t_enemy *enemy, long delay)
{
	long	enemy_elapsed_time;
	get_current_time(&enemy->time1);
	enemy_elapsed_time = get_elapsed_time(&enemy->time0, \
		&enemy->time1);
	if (!enemy->is_dead && enemy_elapsed_time > delay)
	{
		if (enemy->current_animation == enemy->death
			&& enemy->current_frame
			== enemy->current_animation->frame_count - 1)
			enemy->is_dead = 1;
		if (enemy->current_animation \
			== enemy->attack
			&& enemy->current_frame \
			== enemy->current_animation->frame_count - 1)
			enemy->current_animation = enemy->move;
		update_sprite_frame_enemy(enemy);
		enemy->time0 = enemy->time1;
	}
}

void	update_enemy_list(t_enemy *enemy_list, long delay, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		update_enemy_frames(&enemy_list[i], delay);
	}
}

void	setup_imp(t_vars *vars, t_enemy *imp)
{
	imp->x = (imp->grid_x * vars->unit_size);
	imp->y = (imp->grid_y * vars->unit_size);
	imp->center_x = imp->x + vars->unit_size / 2;
	imp->center_y = imp->y + vars->unit_size / 2;
	imp->angle = -M_PI / 2;
	imp->rot_dir = 1;
	imp->fire_ball_x = imp->center_x;
	imp->fire_ball_y = imp->center_y;
	imp->health = 100;
	imp->is_dead = 0;
	imp->current_animation = vars->imp_animation->move;
	imp->move = vars->imp_animation->move;
	imp->death = vars->imp_animation->death;
	imp->attack = vars->imp_animation->attack;
	imp->fire_ball = vars->imp_animation->bullet;
	get_current_time(&imp->time0);
}

void	setup_caco(t_vars *vars, t_enemy *caco)
{
	caco->x = (caco->grid_x * vars->unit_size);
	caco->y = (caco->grid_y * vars->unit_size);
	caco->center_x = caco->x + vars->unit_size / 2;
	caco->center_y = caco->y + vars->unit_size / 2;
	caco->angle = -M_PI / 2;
	caco->rot_dir = 1;
	caco->fire_ball_x = caco->center_x;
	caco->fire_ball_y = caco->center_y;
	caco->health = 100;
	caco->is_dead = 0;
	caco->current_animation = vars->caco_animation->move;
	caco->move = vars->caco_animation->move;
	caco->death = vars->caco_animation->death;
	caco->attack = vars->caco_animation->attack;
	caco->fire_ball = vars->caco_animation->bullet;
	get_current_time(&caco->time0);
}

void	setup_boss(t_vars *vars, t_enemy *boss)
{
	boss->x = (vars->map->boss_x * vars->unit_size);
	boss->y = (vars->map->boss_y * vars->unit_size);
	boss->center_x = boss->x + vars->unit_size / 2;
	boss->center_y = boss->y + vars->unit_size / 2;
	boss->angle = -M_PI / 2;
	boss->rot_dir = 1;
	boss->fire_ball_x = boss->center_x;
	boss->fire_ball_y = boss->center_y;
	boss->health = 1000;
	boss->is_dead = 0;
	boss->current_animation = vars->boss_animation->move;
	boss->move = vars->boss_animation->move;
	boss->death = vars->boss_animation->death;
	boss->attack = vars->boss_animation->attack;
	boss->fire_ball = vars->boss_animation->bullet;
	get_current_time(&boss->time0);
}
