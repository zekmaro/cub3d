/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:44 by anarama           #+#    #+#             */
/*   Updated: 2024/09/12 14:51:42 by iberegsz         ###   ########.fr       */
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

void	free_imp_animations(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	i = 0;
	while (i < 3)
	{
		tmp = (t_img *)vars->imp_animation->attack->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->imp_animation->attack->frames);
	i = 0;
	free(vars->imp_animation->attack);
	while (i < 4)
	{
		tmp = (t_img *)vars->imp_animation->move->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->imp_animation->move->frames);
	i = 0;
	free(vars->imp_animation->move);
	while (i < 5)
	{
		tmp = (t_img *)vars->imp_animation->death->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->imp_animation->death->frames);
	i = 0;
	free(vars->imp_animation->death);
	while (i < 2)
	{
		tmp = (t_img *)vars->imp_animation->bullet->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->imp_animation->bullet->frames);
	free(vars->imp_animation->bullet);
	free(vars->imp_animation);
}

void	free_caco_animations(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	i = 0;
	while (i < 3)
	{
		tmp = (t_img *)vars->caco_animation->attack->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->caco_animation->attack->frames);
	i = 0;
	free(vars->caco_animation->attack);
	while (i < 7)
	{
		tmp = (t_img *)vars->caco_animation->move->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->caco_animation->move->frames);
	i = 0;
	free(vars->caco_animation->move);
	while (i < 5)
	{
		tmp = (t_img *)vars->caco_animation->death->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->caco_animation->death->frames);
	i = 0;
	free(vars->caco_animation->death);
	while (i < 1)
	{
		tmp = (t_img *)vars->caco_animation->bullet->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->caco_animation->bullet->frames);
	free(vars->caco_animation->bullet);
	free(vars->caco_animation);
}

void	free_textures(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		free(vars->textures[i]->mlx_img);
		free(vars->textures[i]);
		i++;
	}
}

void	free_gun(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	i = 0;
	while (i < 4)
	{
		tmp = (t_img *)vars->player->gun->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->player->gun->frames);
	free(vars->player->gun);
}

void	free_fire(t_vars *vars)
{
	int		i;
	t_img	*tmp;

	i = 0;
	while (i < 2)
	{
		tmp = (t_img *)vars->player->fire->frames[i];
		free(tmp->mlx_img);
		free(tmp);
		i++;
	}
	free(vars->player->fire->frames);
	free(vars->player->fire);
}

void	cleanup_vars(t_vars *vars)
{
	free_imp_animations(vars);
	free_caco_animations(vars);
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
