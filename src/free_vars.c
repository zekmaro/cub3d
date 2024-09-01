/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:04:34 by anarama           #+#    #+#             */
/*   Updated: 2024/09/01 14:02:11 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_vars_map(t_vars *vars)
{
	if (vars->map->grid)
		free_map(vars->map);
	free(vars->map);
}

void	free_vars_image(t_vars *vars)
{
	if (vars->image->mlx_img)
	{
		free_vars_textures(vars);
		mlx_destroy_image(vars->mlx->mlx, vars->image->mlx_img);
	}
	free(vars->image);
}

void	free_vars_player(t_vars *vars)
{
	if (vars->player)
		free(vars->player);
}

void	free_vars_mlx(t_vars *vars)
{
	if (vars->mlx->win)
	{
		if (vars->mlx->win)
		{
			mlx_destroy_window(vars->mlx->mlx, vars->mlx->win);
			vars->mlx->win = NULL;
		}
		if (vars->mlx->mlx)
		{
			mlx_destroy_display(vars->mlx->mlx);
			free(vars->mlx->mlx);
			vars->mlx->mlx = NULL;
		}
		free(vars->mlx);
		vars->mlx = NULL;
	}
}

void	free_vars_line(t_vars *vars)
{
	if (vars->line)
		free(vars->line);
}

void	free_vars_sprites(t_vars *vars)
{
	int	i;
	t_img *temp;

	if (vars->animated_sprite)
	{
		if (vars->animated_sprite->frames)
		{
			i = -1;
			while (++i < vars->animated_sprite->frame_count)
				if (vars->animated_sprite->frames[i])
				{
					temp = (t_img *)vars->animated_sprite->frames[i];
					free(temp->mlx_img);
					free(vars->animated_sprite->frames[i]);
				}
			free(vars->animated_sprite->frames);
		}
		free(vars->animated_sprite);
		vars->animated_sprite = NULL;
	}
}
