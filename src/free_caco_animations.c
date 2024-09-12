/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_caco_animations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:12:34 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 01:12:41 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_caco_animations(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	i = 0;
	while (i < 3)
	{
		tmp = (t_img *)vars->caco_animation->attack->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->caco_animation->attack->frames);
	i = 0;
	free(vars->caco_animation->attack);
	while (i < 7)
	{
		tmp = (t_img *)vars->caco_animation->move->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->caco_animation->move->frames);
	i = 0;
	free(vars->caco_animation->move);
	while (i < 5)
	{
		tmp = (t_img *)vars->caco_animation->death->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->caco_animation->death->frames);
	i = 0;
	free(vars->caco_animation->death);
	while (i < 1)
	{
		tmp = (t_img *)vars->caco_animation->bullet->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->caco_animation->bullet->frames);
	free(vars->caco_animation->bullet);
	free(vars->caco_animation);
}
