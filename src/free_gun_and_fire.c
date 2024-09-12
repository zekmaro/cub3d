/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gun_and_fire.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:20:49 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 01:21:07 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_gun(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	i = 0;
	while (i < 4)
	{
		tmp = (t_img *)vars->player->gun->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->player->gun->frames);
	free(vars->player->gun);
}

void	free_fire(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	i = 0;
	while (i < 2)
	{
		tmp = (t_img *)vars->player->fire->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->player->fire->frames);
	free(vars->player->fire);
}
