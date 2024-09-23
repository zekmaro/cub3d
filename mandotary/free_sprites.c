/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:44:14 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/20 22:09:33 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_vars_sprites(t_vars *vars)
{
	if (vars == NULL)
		return ;
	if (vars->sprites)
	{
		free(vars->sprites);
		vars->sprites = NULL;
	}
}

void	free_sprite_frame(t_img *frame)
{
	if (frame == NULL)
		return ;
	if (frame)
	{
		if (frame->mlx_img)
		{
			free(frame->mlx_img);
			frame->mlx_img = NULL;
		}
		free(frame);
	}
}
