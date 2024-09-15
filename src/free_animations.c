/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:57:17 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/15 20:04:32 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_animation(t_img **animation, int frame_count)
{
	if (*animation != NULL)
	{
		free_animated_frames((t_img **)(*animation)->frames, frame_count);
		free(*animation);
		*animation = NULL;
	}
}

void	free_imp_animations(t_vars *vars)
{
	if (vars == NULL || vars->imp_animation == NULL)
		return ;
	free_animation(&vars->imp_animation->attack, 3);
	free_animation(&vars->imp_animation->move, 4);
	free_animation(&vars->imp_animation->death, 5);
	free_animation(&vars->imp_animation->bullet, 2);
	free(vars->imp_animation);
	vars->imp_animation = NULL;
}

void	free_caco_animations(t_vars *vars)
{
	if (vars == NULL || vars->caco_animation == NULL)
		return ;
	free_animation(&vars->caco_animation->attack, 3);
	free_animation(&vars->caco_animation->move, 7);
	free_animation(&vars->caco_animation->death, 5);
	free_animation(&vars->caco_animation->bullet, 1);
	free(vars->caco_animation);
	vars->caco_animation = NULL;
}

void	free_boss_animations(t_vars *vars)
{
	if (vars == NULL || vars->boss_animation == NULL)
		return ;
	free_animation(&vars->boss_animation->attack, 2);
	free_animation(&vars->boss_animation->move, 4);
	free_animation(&vars->boss_animation->death, 9);
	free_animation(&vars->boss_animation->bullet, 1);
	free(vars->boss_animation);
	vars->boss_animation = NULL;
	free(vars->boss);
	vars->boss = NULL;
}
