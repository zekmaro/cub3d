/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:44:14 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 12:26:24 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_sprites(t_vars *vars)
{
	if (!vars)
		return ;
}

void	free_vars_sprites(t_vars *vars)
{
	if (vars->sprites)
	{
		free(vars->sprites);
		vars->sprites = NULL;
	}
}

void	free_vars_animated_sprite(t_vars *vars)
{
	int		i;
	t_img	*temp;

	if (vars->animated_sprite)
	{
		if (vars->animated_sprite->frames)
		{
			i = -1;
			while (++i < vars->animated_sprite->frame_count)
			{
				if (vars->animated_sprite->frames[i])
				{
					temp = (t_img *)vars->animated_sprite->frames[i];
					if (temp->mlx_img)
					{
						free(temp->mlx_img);
						temp->mlx_img = NULL;
					}
					free(vars->animated_sprite->frames[i]);
					vars->animated_sprite->frames[i] = NULL;
				}
			}
			free(vars->animated_sprite->frames);
			vars->animated_sprite->frames = NULL;
		}
		free(vars->animated_sprite);
		vars->animated_sprite = NULL;
	}
}
