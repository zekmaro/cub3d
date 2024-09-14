/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:48:15 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/14 22:51:15 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_textures(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (vars->textures[i])
		{
			if (vars->textures[i]->mlx_img)
				free(vars->textures[i]->mlx_img);
			free(vars->textures[i]);
			vars->textures[i] = NULL;
		}
		i++;
	}
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
			vars->textures[i] = NULL;
		}
	}
}

void	free_vars_sprite_texture(t_vars *vars)
{
	if (vars->sprite_texture)
	{
		free(vars->sprite_texture);
		vars->sprite_texture = NULL;
	}
}

void	free_vars_fire(t_vars *vars)
{
	if (vars->player->fire)
	{
		free(vars->player->fire);
		vars->player->fire = NULL;
	}
}
