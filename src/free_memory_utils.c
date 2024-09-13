/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:44 by anarama           #+#    #+#             */
/*   Updated: 2024/09/13 17:56:10 by anarama          ###   ########.fr       */
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
	free_imp_animations(vars);
	free_caco_animations(vars);
	free_boss_animations(vars);
	free_enemy_list(vars);
	free_textures(vars);
	free_doors(vars);
	free_gun(vars);
	free_fire(vars);
	free_vars_map(vars);
	free_vars_image(vars);
	free_vars_mlx(vars);
	free_vars_line(vars);
	free_vars_player(vars);
	free_vars_ray(vars);
	free_vars_sprites(vars);
	free_vars_zbuffer(vars);
}
