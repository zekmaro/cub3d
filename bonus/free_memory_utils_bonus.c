/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:44 by anarama           #+#    #+#             */
/*   Updated: 2024/09/24 16:58:40 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_memory(char **arr)
{
	char	**temp;

	if (!arr)
		return ;
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
	if (vars == NULL)
		return ;
	if (vars->zbuffer)
	{
		free(vars->zbuffer);
		vars->zbuffer = NULL;
	}
}

int	free_and_exit(t_vars *vars)
{
	if (vars == NULL)
		return (0);
	cleanup_vars(vars);
	exit(0);
}

void	exit_with_error(t_vars *vars, char *error_message)
{
	if (vars == NULL)
		return ;
	ft_putstr_fd(error_message, 2);
	free_and_exit(vars);
}

void	cleanup_vars(t_vars *vars)
{
	if (vars == NULL)
		return ;
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
	free_vars_texture_names(vars);
}
