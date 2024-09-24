/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gun_and_fire_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:20:49 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/24 16:58:37 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_gun(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	if (vars == NULL)
		return ;
	if (vars->player && vars->player->gun && vars->player->gun->frames)
	{
		i = 0;
		while (i < 4)
		{
			tmp = (t_img *)vars->player->gun->frames[i];
			if (tmp)
			{
				if (tmp->mlx_img)
					free(tmp->mlx_img);
				free(tmp);
			}
			i++;
		}
		free(vars->player->gun->frames);
		free(vars->player->gun);
	}
}

void	free_fire(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	if (vars == NULL)
		return ;
	if (vars->player && vars->player->fire && vars->player->fire->frames)
	{
		i = 0;
		while (i < 2)
		{
			tmp = (t_img *)vars->player->fire->frames[i];
			if (tmp)
			{
				if (tmp->mlx_img)
					free(tmp->mlx_img);
				free(tmp);
			}
			i++;
		}
		free(vars->player->fire->frames);
		free(vars->player->fire);
	}
}
