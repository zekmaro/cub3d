/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:04:34 by anarama           #+#    #+#             */
/*   Updated: 2024/09/12 14:58:00 by iberegsz         ###   ########.fr       */
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

void	free_doors(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	i = 0;
	while (i < 4)
	{
		tmp = (t_img *)vars->door->textures->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->door->textures->frames);
	free(vars->door->textures);
	free(vars->door);
}

void	free_environment(t_vars *vars)
{
	free_vars_animated_sprite(vars);
	free_vars_gun(vars);
	free_vars_fire(vars);
	free_vars_door_textures(vars);
	free_vars_sprite_texture(vars);
	free_vars_sprites(vars);
	free_vars_zbuffer(vars);
}
// void	free_vars_doors(t_vars *vars)
// {
// 	int	i;

// 	if (vars->map->doors)
// 	{
// 		free(vars->map->doors);
// 		vars->map->doors = NULL;
// 	}
// 	if (vars->door_textures)
// 	{
// 		i = -1;
// 		while (++i < 4)
// 		{
// 			if (vars->door_textures[i].mlx_img)
// 				mlx_destroy_image(vars->mlx, vars->door_textures[i].mlx_img);
// 		}
// 		free(vars->door_textures);
// 		vars->door_textures = NULL;
// 	}
// }
