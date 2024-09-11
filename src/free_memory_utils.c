/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:44 by anarama           #+#    #+#             */
/*   Updated: 2024/09/11 14:56:07 by anarama          ###   ########.fr       */
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

void	free_animated_sprite_if_exists(t_img **sprite)
{
	if (*sprite)
	{
		free_animated_sprite(*sprite);
		*sprite = NULL;
	}
}

void	free_texture_if_exists(t_vars *vars, t_img **texture)
{
	if (*texture)
	{
		if ((*texture)->mlx_img)
		{
			mlx_destroy_image(vars->mlx->mlx, (*texture)->mlx_img);
			(*texture)->mlx_img = NULL;
		}
		free(*texture);
		*texture = NULL;
	}
}

void	free_sprites(t_vars *vars)
{
	if (!vars)
		return ;
	free_animated_sprite_if_exists(&vars->player->gun);
	free_animated_sprite_if_exists(&vars->player->fire);
	free_animated_sprite_if_exists(&vars->door->textures);
	free_texture_if_exists(vars, &vars->sprite_texture);
	if (vars->sprites)
	{
		free(vars->sprites);
		vars->sprites = NULL;
	}
}

// void	free_imp_list(t_vars *vars)
// {
// 	int	i;

// 	if (vars->imp_list)
// 	{
// 		i = 0;
// 		while (i < vars->map->imp_list_size)
// 		{
// 			free(vars->imp_list[i].move_animation);
// 			free(vars->imp_list[i].death_animation);
// 			free(vars->imp_list[i].attack_animation);
// 			free(vars->imp_list[i].fire_ball);
// 			i++;
// 		}
// 		free(vars->imp_list);
// 	}
// }

// void	free_caco_list(t_vars *vars)
// {
// 	int	i;

// 	if (vars->caco_list)
// 	{
// 		i = 0;
// 		while (i < vars->map->caco_list_size)
// 		{
// 			free(vars->caco_list[i].move_animation);
// 			free(vars->caco_list[i].death_animation);
// 			free(vars->caco_list[i].attack_animation);
// 			free(vars->caco_list[i].fire_ball);
// 			i++;
// 		}
// 		free(vars->caco_list);
// 	}
// }

// void	free_enemy_list(t_vars *vars)
// {
// 	free_imp_list(vars);
// 	free_caco_list(vars);
// }

void	free_doors(t_vars *vars)
{
	if (vars->door)
	{
		free(vars->door);
		vars->door = NULL;
	}
}

int	free_and_exit(t_vars *vars)
{
	cleanup_vars(vars);
	exit(0);
}

void	cleanup_vars(t_vars *vars)
{
	//free_enemy_list(vars);
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
