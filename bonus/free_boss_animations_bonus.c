/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_boss_animations_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:50:48 by anarama           #+#    #+#             */
/*   Updated: 2024/09/24 16:58:08 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_boss_animations(t_vars *vars)
{
	if (vars->boss_animation == NULL)
		return ;
	if (vars->boss_animation->attack != NULL)
	{
		free_animated_frames((t_img **)vars->boss_animation->attack->frames, 2);
		free(vars->boss_animation->attack);
	}
	if (vars->boss_animation->move != NULL)
	{
		free_animated_frames((t_img **)vars->boss_animation->move->frames, 4);
		free(vars->boss_animation->move);
	}
	if (vars->boss_animation->death != NULL)
	{
		free_animated_frames((t_img **)vars->boss_animation->death->frames, 9);
		free(vars->boss_animation->death);
	}
	if (vars->boss_animation->bullet != NULL)
	{
		free_animated_frames((t_img **)vars->boss_animation->bullet->frames, 1);
		free(vars->boss_animation->bullet);
	}
	free(vars->boss_animation);
	free(vars->boss);
}
