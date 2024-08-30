/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:44 by anarama           #+#    #+#             */
/*   Updated: 2024/08/30 19:07:15 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
}

int	free_and_exit(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	cleanup_vars(vars);
	exit(0);
}

void free_vars_textures(t_vars *vars)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (vars->textures[i])
		{
			mlx_destroy_image(vars->mlx->mlx, vars->textures[i]);
			vars->textures[i] = NULL;
		}
	}
}

void	cleanup_vars(t_vars *vars)
{
	free_vars_map(vars);
	free_vars_image(vars);
	free_vars_textures(vars);
	free_vars_mlx(vars);
	free_vars_line(vars);
	free_vars_player(vars);	
}
