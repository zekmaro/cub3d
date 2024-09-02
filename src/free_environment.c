/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:04:34 by anarama           #+#    #+#             */
/*   Updated: 2024/09/02 12:21:16 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_vars_map(t_vars *vars)
{
	if (vars->map->grid)
		free_map(vars->map);
	free(vars->map);
}

void	free_vars_textures(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (vars->textures[i])
		{
			free(vars->textures[i]->mlx_img);
			free(vars->textures[i]);
		}
	}
}

void	free_vars_sprites(t_vars *vars)
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
					free(temp->mlx_img);
					free(vars->animated_sprite->frames[i]);
				}
			}
			free(vars->animated_sprite->frames);
		}
		free(vars->animated_sprite);
		vars->animated_sprite = NULL;
	}
}
