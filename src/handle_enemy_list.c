/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:46:23 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 02:35:49 by iberegsz         ###   ########.fr       */
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
		if (!enemy_list[i].is_dead && enemy_elapsed_time > delay)
		{
			if (enemy_list[i].health == 0)
			{
				printf("current frame %d index %d action %p\n", \
					enemy_list[i].current_frame, i,  \
					enemy_list[i].current_animation);
			}
			if (enemy_list[i].current_animation == enemy_list[i].death
				&& enemy_list[i].current_frame
				== enemy_list[i].current_animation->frame_count - 1)
			{
				enemy_list[i].is_dead = 1;
			}
			if (enemy_list[i].current_animation \
				== enemy_list[i].attack
				&& enemy_list[i].current_frame \
				== enemy_list[i].current_animation->frame_count - 1)
				enemy_list[i].current_animation = enemy_list[i].move;
			update_sprite_frame_enemy(&enemy_list[i]);
			enemy_list[i].time0 = enemy_list[i].time1;
		}
	}
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
