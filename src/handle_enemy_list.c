/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:46:23 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 23:07:24 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cleanup_enemy_lists(t_vars *vars)
{
	if (vars->imp_list)
	{
		free(vars->imp_list);
		vars->imp_list = NULL;
	}
	if (vars->caco_list)
	{
		free(vars->caco_list);
		vars->caco_list = NULL;
	}
}

void	init_enemy_lists(t_vars *vars)
{
	vars->imp_list = ft_calloc(sizeof(t_enemy), vars->map->imp_list_size);
	if (!vars->imp_list)
	{
		exit_with_error(vars, "Failed to allocate memory for imp list");
	}
	vars->caco_list = ft_calloc(sizeof(t_enemy), vars->map->caco_list_size);
	if (!vars->caco_list)
	{
		cleanup_enemy_lists(vars);
		exit_with_error(vars, "Failed to allocate memory for caco list");
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
