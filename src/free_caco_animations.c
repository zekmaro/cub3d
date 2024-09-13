/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_caco_animations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:12:34 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 02:32:38 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_caco_animations(t_vars *vars)
{
	if (vars->caco_animation == NULL)
		return ;
	if (vars->caco_animation->attack != NULL)
	{
		free_animated_frames((t_img **)vars->caco_animation->attack->frames, 3);
		free(vars->caco_animation->attack);
	}
	if (vars->caco_animation->move != NULL)
	{
		free_animated_frames((t_img **)vars->caco_animation->move->frames, 7);
		free(vars->caco_animation->move);
	}
	if (vars->caco_animation->death != NULL)
	{
		free_animated_frames((t_img **)vars->caco_animation->death->frames, 5);
		free(vars->caco_animation->death);
	}
	if (vars->caco_animation->bullet != NULL)
	{
		free_animated_frames((t_img **)vars->caco_animation->bullet->frames, 1);
		free(vars->caco_animation->bullet);
	}
	free(vars->caco_animation);
}
