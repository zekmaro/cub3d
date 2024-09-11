/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:51:57 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/11 22:00:01 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_imp_list(t_vars *vars)
{
	int	i;

	if (vars->imp_list)
	{
		i = 0;
		while (i < vars->map->imp_list_size)
		{
			// free(vars->imp_list[i].move_animation);
			// free(vars->imp_list[i].death_animation);
			// free(vars->imp_list[i].attack_animation);
			// free(vars->imp_list[i].fire_ball);
			i++;
		}
		free(vars->imp_list);
	}
}

void	free_caco_list(t_vars *vars)
{
	int	i;

	if (vars->caco_list)
	{
		i = 0;
		while (i < vars->map->caco_list_size)
		{
			// free(vars->caco_list[i].move_animation);
			// free(vars->caco_list[i].death_animation);
			// free(vars->caco_list[i].attack_animation);
			// free(vars->caco_list[i].fire_ball);
			i++;
		}
		free(vars->caco_list);
	}
}

void	free_enemy_list(t_vars *vars)
{
	free_imp_list(vars);
	free_caco_list(vars);
}
