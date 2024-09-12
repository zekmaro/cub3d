/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_imp_animations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:11:28 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 01:11:56 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_imp_animations(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	i = 0;
	while (i < 3)
	{
		tmp = (t_img *)vars->imp_animation->attack->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->imp_animation->attack->frames);
	i = 0;
	free(vars->imp_animation->attack);
	while (i < 4)
	{
		tmp = (t_img *)vars->imp_animation->move->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->imp_animation->move->frames);
	i = 0;
	free(vars->imp_animation->move);
	while (i < 5)
	{
		tmp = (t_img *)vars->imp_animation->death->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->imp_animation->death->frames);
	i = 0;
	free(vars->imp_animation->death);
	while (i < 2)
	{
		tmp = (t_img *)vars->imp_animation->bullet->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->imp_animation->bullet->frames);
	free(vars->imp_animation->bullet);
	free(vars->imp_animation);
}
