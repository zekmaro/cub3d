/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:46:23 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/11 01:53:37 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_enemy_lists(t_vars *vars)
{
	vars->imp_list = ft_calloc(sizeof(t_enemy), vars->map->imp_list_size);
	vars->caco_list = ft_calloc(sizeof(t_enemy), vars->map->caco_list_size);
}

void	handle_enemy_death(t_enemy *enemy)
{
	if (enemy->current_animation == enemy->death_animation \
		&& enemy->current_animation->current_frame \
		== enemy->death_animation->frame_count - 1)
	{
		enemy->is_dead = 1;
		enemy->center_x = -100;
		enemy->center_y = -100;
	}
}

void	handle_enemy_attack(t_enemy *enemy)
{
	if (enemy->current_animation == enemy->attack_animation \
		&& enemy->current_animation->current_frame \
		== enemy->attack_animation->frame_count - 1)
	{
		enemy->current_animation = enemy->move_animation;
	}
}

void	update_enemy(t_enemy *enemy, long delay)
{
	long	enemy_elapsed_time;

	get_current_time(&enemy->time1);
	enemy_elapsed_time = get_elapsed_time(&enemy->time0, &enemy->time1);
	if (enemy_elapsed_time > delay)
	{
		handle_enemy_death(enemy);
		update_sprite_frame(enemy->current_animation);
		handle_enemy_attack(enemy);
		enemy->time0 = enemy->time1;
	}
}

void	update_enemy_list(t_enemy *enemy_list, long delay, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		update_enemy(&enemy_list[i], delay);
}

long	update_imp_time(t_vars *vars)
{
	long	elapsed_time;

	get_current_time(&vars->imp->time1);
	elapsed_time = get_elapsed_time(&vars->imp->time0, &vars->imp->time1);
	return (elapsed_time);
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
	imp->move_animation = ft_calloc(sizeof(t_img), 1);
	imp->death_animation = ft_calloc(sizeof(t_img), 1);
	imp->attack_animation = ft_calloc(sizeof(t_img), 1);
	imp->fire_ball = ft_calloc(sizeof(t_img), 1);
	get_current_time(&imp->time0);
	init_imp_sprites(vars, imp);
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
	caco->move_animation = ft_calloc(sizeof(t_img), 1);
	caco->death_animation = ft_calloc(sizeof(t_img), 1);
	caco->attack_animation = ft_calloc(sizeof(t_img), 1);
	caco->fire_ball = ft_calloc(sizeof(t_img), 1);
	get_current_time(&caco->time0);
	init_caco_sprites(vars, caco);
}
