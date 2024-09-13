/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:44:14 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 02:36:49 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_animated_sprite(t_vars *vars, t_img *sprite)
{
	int		i;
	t_img	*tmp;

	if (sprite)
	{
		if (sprite->frames)
		{
			i = -1;
			while (++i < sprite->frame_count)
			{
				if (sprite->frames[i])
				{
					tmp = (t_img *)sprite->frames[i];
					if (tmp->mlx_img)
					{
						mlx_destroy_image(vars->mlx->mlx, tmp->mlx_img);
						tmp->mlx_img = NULL;
					}
					free(sprite->frames[i]);
					sprite->frames[i] = NULL;
				}
			}
			free(sprite->frames);
			sprite->frames = NULL;
		}
		free(sprite);
		sprite = NULL;
	}
}

void	free_animated_sprite_if_exists(t_vars *vars, t_img **sprite)
{
	if (sprite && *sprite)
	{
		free_animated_sprite(vars, *sprite);
		*sprite = NULL;
	}
}

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
