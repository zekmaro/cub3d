/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:32:18 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/14 23:35:56 by iberegsz         ###   ########.fr       */
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
		exit_with_error(vars, "Failed to allocate memory for map");
		return ;
	}
	ft_bzero(map, sizeof(t_map));
	vars->map = map;
}

void	initialise_zbuffer(t_vars *vars)
{
	vars->zbuffer = malloc(sizeof(int) * vars->mlx->window_width);
	if (!vars->zbuffer)
	{
		exit_with_error(vars, "Failed to allocate memory for zbuffer");
		return ;
	}
	ft_bzero(vars->zbuffer, sizeof(int) * vars->mlx->window_width);
}

void	initialise_doors(t_vars *vars)
{
	t_door	*doors;

	doors = ft_calloc(vars->map->num_doors, sizeof(t_door));
	if (!doors)
	{
		exit_with_error(vars, "Failed to allocate memory for doors");
		return ;
	}
	ft_bzero(doors, sizeof(t_door));
	vars->doors = doors;
}

void	initialise_vars(t_vars *vars)
{
	vars->unit_size = 64;
	ft_bzero(vars->textures, sizeof(vars->textures));
	ft_bzero(vars->texture_names, sizeof(vars->texture_names));
	initialise_image(vars);
	initialise_map(vars);
	initialise_mlx(vars);
	initialise_line(vars);
	initialise_ray(vars);
	initialise_player(vars);
	initialise_zbuffer(vars);
}
