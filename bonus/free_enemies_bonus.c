/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_enemies_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:51:57 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/24 16:58:33 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_imp_list(t_vars *vars)
{
	if (vars == NULL)
		return ;
	if (vars->imp_list)
		free(vars->imp_list);
}

void	free_caco_list(t_vars *vars)
{
	if (vars == NULL)
		return ;
	if (vars->caco_list)
		free(vars->caco_list);
}

void	free_enemy_list(t_vars *vars)
{
	if (vars == NULL)
		return ;
	free(vars->caco_list);
	free(vars->imp_list);
}
