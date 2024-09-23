/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_enemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:22:37 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 18:23:12 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
