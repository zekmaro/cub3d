/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:32:18 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/10 01:35:21 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_frames(const char **frames)
{
	int	result;

	result = 0;
	while (*frames)
	{
		result++;
		frames++;
	}
	return (result);
}

void	initialise_map(t_vars *vars)
{
	t_map	*map;

	map = (t_map *)(malloc(sizeof(t_map)));
	if (!map)
	{
		cleanup_vars(vars);
	}
	ft_bzero(map, sizeof(t_map));
	vars->map = map;
}

void	initialise_zbuffer(t_vars *vars)
{
	vars->zbuffer = malloc(sizeof(int) * vars->mlx->window_width);
	if (!vars->zbuffer)
	{
		perror("Failed to allocate memory for zbuffer");
		free_and_exit(vars);
	}
}

void	initialise_doors(t_vars *vars)
{
	vars->map->num_doors = 0;
	vars->door = ft_calloc(1, sizeof(t_door));
	if (!vars->door)
	{
		perror("Failed to allocate memory for doors");
		free_and_exit(vars);
	}
}

void	initialise_vars(t_vars *vars)
{
	vars->unit_size = 64;
	ft_bzero(vars->textures, sizeof(vars->textures));
	initialise_image(vars);
	initialise_map(vars);
	initialise_doors(vars);
	initialise_mlx(vars);
	initialise_line(vars);
	initialise_ray(vars);
	initialise_player(vars);
	initialise_zbuffer(vars);
}
