/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:44 by anarama           #+#    #+#             */
/*   Updated: 2024/09/10 20:34:54 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

void	free_memory(char **arr)
{
	char	**temp;

	temp = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(temp);
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
	// if (map->doors)
	// {
	// 	// i = 0;
	// 	// while (i < map->num_doors)
	// 	// {
	// 	// 	free(map->doors[i]);
	// 	// 	i++;
	// 	// }
	// 	free(map->doors);
	// }
}

void	free_animated_sprite(t_img *sprite)
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
					free(tmp->mlx_img);
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

void	free_sprites(t_vars *vars)
{
	if (vars->player->gun)
	{
		free_animated_sprite(vars->player->gun);
		vars->player->gun = NULL;
	}
	if (vars->player->fire)
	{
		free_animated_sprite(vars->player->fire);
		vars->player->fire = NULL;
	}
	if (vars->door->textures)
	{
		free_animated_sprite(vars->door->textures);
		vars->door->textures = NULL;
	}
	if (vars->sprite_texture)
	{
		if (vars->sprite_texture->mlx_img)
		{
			mlx_destroy_image(vars->mlx->mlx, vars->sprite_texture->mlx_img);
			vars->sprite_texture->mlx_img = NULL;
		}
		free(vars->sprite_texture);
		vars->sprite_texture = NULL;
	}
	if (vars->sprites)
	{
		free(vars->sprites);
		vars->sprites = NULL;
	}
}

int	free_and_exit(t_vars *vars)
{
	cleanup_vars(vars);
	exit(0);
}

void	cleanup_vars(t_vars *vars)
{
	free_sprites(vars);
	free_environment(vars);
	free_vars_map(vars);
	free_vars_image(vars);
	free_vars_mlx(vars);
	free_vars_line(vars);
	free_vars_player(vars);
	free_vars_ray(vars);
	free_vars_sprites(vars);
	free_vars_zbuffer(vars);
}
//free_vars_doors(vars);
