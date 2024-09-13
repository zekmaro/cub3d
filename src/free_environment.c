/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:04:34 by anarama           #+#    #+#             */
/*   Updated: 2024/09/13 22:53:31 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_vars_map(t_vars *vars)
{
	if (vars->map)
	{
		free_map(vars->map);
		free(vars->map);
		vars->map = NULL;
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

void	free_vars_gun(t_vars *vars)
{
	if (vars->player->gun)
	{
		free(vars->player->gun);
		vars->player->gun = NULL;
	}
}

void	free_frames(t_img **frames, int count)
{
	int		i;
	t_img	*tmp;

	i = -1;
	while (++i < count)
	{
		tmp = frames[i];
		if (tmp)
		{
			if (tmp->mlx_img)
				free(tmp->mlx_img);
			free(tmp);
		}
	}
}

void	free_doors(t_vars *vars)
{
	if (vars->door)
	{
		if (vars->door->textures)
		{
			if (vars->door->textures->frames)
			{
				free_frames((t_img **)vars->door->textures->frames, 4);
				free(vars->door->textures->frames);
			}
			free(vars->door->textures);
		}
		free(vars->door);
	}
}
