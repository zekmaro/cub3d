/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:44 by anarama           #+#    #+#             */
/*   Updated: 2024/09/11 22:10:27 by iberegsz         ###   ########.fr       */
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

void	free_vars_zbuffer(t_vars *vars)
{
	if (vars->zbuffer)
	{
		free(vars->zbuffer);
		vars->zbuffer = NULL;
	}
}

int	free_and_exit(t_vars *vars)
{
	cleanup_vars(vars);
	exit(0);
}

void	exit_with_error(t_vars *vars, char *error_message)
{
	perror(error_message);
	free_and_exit(vars);
}

void	cleanup_vars(t_vars *vars)
{
	free_enemy_list(vars);
	free_sprites(vars);
	free_environment(vars);
	free_doors(vars);
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
