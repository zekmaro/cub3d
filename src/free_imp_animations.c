/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_imp_animations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:11:28 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 02:33:13 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_imp_animations(t_vars *vars)
{
	if (vars->imp_animation == NULL)
		return ;
	if (vars->imp_animation->attack != NULL)
	{
		free_animated_frames((t_img **)vars->imp_animation->attack->frames, 3);
		free(vars->imp_animation->attack);
	}
	if (vars->imp_animation->move != NULL)
	{
		free_animated_frames((t_img **)vars->imp_animation->move->frames, 4);
		free(vars->imp_animation->move);
	}
	if (vars->imp_animation->death != NULL)
	{
		free_animated_frames((t_img **)vars->imp_animation->death->frames, 5);
		free(vars->imp_animation->death);
	}
	if (vars->imp_animation->bullet != NULL)
	{
		free_animated_frames((t_img **)vars->imp_animation->bullet->frames, 2);
		free(vars->imp_animation->bullet);
	}
	free(vars->imp_animation);
}
