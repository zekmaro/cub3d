/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environment_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:04:34 by anarama           #+#    #+#             */
/*   Updated: 2024/09/24 16:58:35 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_vars_map(t_vars *vars)
{
	if (vars == NULL)
		return ;
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

	if (map == NULL || map->grid == NULL)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
		}
		i++;
	}
	if (map->grid)
	{
		free(map->grid);
		map->grid = NULL;
	}
}

void	free_vars_gun(t_vars *vars)
{
	if (vars == NULL)
		return ;
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

	if (frames == NULL)
		return ;
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
	if (vars == NULL)
		return ;
	if (vars->doors)
	{
		if (vars->doors->textures)
		{
			if (vars->doors->textures->frames)
			{
				free_frames((t_img **)vars->doors->textures->frames, 4);
				free(vars->doors->textures->frames);
			}
			free(vars->doors->textures);
		}
		free(vars->doors);
		vars->doors = NULL;
	}
}
