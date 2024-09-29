/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:30:03 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/29 20:31:10 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	setup_player(t_vars *vars)
{
	double	plane_length;

	vars->player->x = (vars->map->player_x * vars->unit_size) \
		+ vars->unit_size / 2;
	vars->player->y = (vars->map->player_y * vars->unit_size) \
		+ vars->unit_size / 2;
	vars->player->fov = M_PI / 3;
	if (vars->map->player_dir == 'N')
		vars->player->angle = -M_PI / 2;
	else if (vars->map->player_dir == 'W')
		vars->player->angle = -M_PI;
	else if (vars->map->player_dir == 'S')
		vars->player->angle = -3 * M_PI / 2;
	else if (vars->map->player_dir == 'E')
		vars->player->angle = 0;
	vars->player->dir_x = cos(vars->player->angle);
	vars->player->dir_y = sin(vars->player->angle);
	plane_length = tan(vars->player->fov / 2);
	vars->player->plane_x = -vars->player->dir_y * plane_length;
	vars->player->plane_y = vars->player->dir_x * plane_length;
	vars->player->health = 1000;
}

int	player_damaged_enemy(t_vars *vars, t_enemy *enemy)
{
	return (ft_abs(enemy->fire_ball_x - vars->player->center_x) < 20
		&& ft_abs(enemy->fire_ball_y - vars->player->center_y) < 20
		&& !vars->player->is_damaged);
}

void	update_damaged_player(t_vars *vars)
{
	vars->player->is_damaged = 1;
	vars->player->health -= 20;
	get_current_time(&vars->player->time0);
	if (vars->player->health == 0)
	{
		ft_putstr_fd("GAME OVER!\n", 1);
		free_and_exit(vars);
	}
}

void	handle_player_damaged_time(t_vars *vars)
{
	long	time_player_damaged;

	time_player_damaged = get_elapsed_time(&vars->player->time0, \
		&vars->player->time1);
	if (time_player_damaged > 500)
		vars->player->is_damaged = 0;
}

void	handle_enemy_shot(t_vars *vars, t_enemy *enemy)
{
	if (player_damaged_enemy(vars, enemy))
	{
		update_damaged_player(vars);
		enemy->fire_ball_y = 0;
		enemy->fire_ball_x = 0;
	}
	else
	{
		enemy->fire_ball_y += enemy->fire_delta_y;
		enemy->fire_ball_x += enemy->fire_delta_x;
	}
}
