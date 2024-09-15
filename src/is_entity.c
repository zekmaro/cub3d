/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_entity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:00:29 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/12 13:43:36 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_player(t_vars *vars, int y, int x)
{
	return (abs(y - vars->player->center_y) < 10 \
		&& abs(x - vars->player->center_x) < 10);
}

int	is_enemy(t_enemy *enemy, int y, int x)
{
	return (abs(y - enemy->center_y) < 20 && abs(x - enemy->center_x) < 20);
}

int	is_imp(t_vars *vars, int y, int x)
{
	return (abs(y - vars->imp->center_y) < 40 \
		&& abs(x - vars->imp->center_x) < 40);
}

int	is_caco(t_vars *vars, int y, int x)
{
	return (abs(y - vars->caco->center_y) < 40 \
		&& abs(x - vars->caco->center_x) < 40);
}
