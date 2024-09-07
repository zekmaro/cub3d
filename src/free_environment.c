/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:04:34 by anarama           #+#    #+#             */
/*   Updated: 2024/09/07 18:08:12 by iberegsz         ###   ########.fr       */
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

void	free_vars_line(t_vars *vars)
{
	if (vars->line)
		free(vars->line);
}

void	free_vars_doors(t_vars *vars)
{
	int	i;

	if (vars->map->doors)
	{
		free(vars->map->doors);
		vars->map->doors = NULL;
	}
	if (vars->door_textures)
	{
		i = -1;
		while (++i < 4)
		{
			if (vars->door_textures[i].mlx_img)
				mlx_destroy_image(vars->mlx, vars->door_textures[i].mlx_img);
		}
		free(vars->door_textures);
		vars->door_textures = NULL;
	}
}

// void	free_vars_sprites(t_vars *vars)
// {
// 	int		i;
// 	t_img	*temp;

// 	if (vars->animated_sprite)
// 	{
// 		if (vars->animated_sprite->frames)
// 		{
// 			i = -1;
// 			while (++i < vars->animated_sprite->frame_count)
// 			{
// 				if (vars->animated_sprite->frames[i])
// 				{
// 					temp = (t_img *)vars->animated_sprite->frames[i];
// 					free(temp->mlx_img);
// 					free(vars->animated_sprite->frames[i]);
// 				}
// 			}
// 			free(vars->animated_sprite->frames);
// 		}
// 		free(vars->animated_sprite);
// 		vars->animated_sprite = NULL;
// 	}
// }

void	free_vars_zbuffer(t_vars *vars)
{
	if (vars->zbuffer)
	{
		free(vars->zbuffer);
		vars->zbuffer = NULL;
	}
}
