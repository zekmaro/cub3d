/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:12:34 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 13:31:40 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_texture(t_vars *vars, int texture_index, const char *file_path)
{
	int	width;
	int	height;

	vars->textures[texture_index] = mlx_xpm_file_to_image(vars->mlx->mlx, \
		(char *)file_path, &width, &height);
	if (!vars->textures[texture_index])
	{
		perror("Failed to load texture");
		free_and_exit(vars);
	}
	vars->textures[texture_index]->addr = mlx_get_data_addr(\
		vars->textures[texture_index], \
		&vars->textures[texture_index]->bits_per_pixel, \
		&vars->textures[texture_index]->line_len, \
		&vars->textures[texture_index]->endian);
	if (!vars->textures[texture_index]->addr)
	{
		perror("Failed to get texture data address");
		free_and_exit(vars);
	}
	vars->textures[texture_index]->width = width;
	vars->textures[texture_index]->height = height;
}

void	initialise_textures(t_vars *vars)
{
	if (!vars->mlx || !vars->mlx->mlx)
	{
		perror("MLX not initialized");
		free_and_exit(vars);
	}
	load_texture(vars, TEXTURE_NORTH, "./assets/wall1.xpm");
	load_texture(vars, TEXTURE_SOUTH, "./assets/wall2.xpm");
	load_texture(vars, TEXTURE_WEST, "./assets/wall3.xpm");
	load_texture(vars, TEXTURE_EAST, "./assets/wall4.xpm");
	load_texture(vars, TEXTURE_DOOR0, "./assets/door0.xpm");
	load_texture(vars, TEXTURE_DOOR1, "./assets/door1.xpm");
	load_texture(vars, TEXTURE_DOOR2, "./assets/door2.xpm");
	load_texture(vars, TEXTURE_DOOR3, "./assets/door3.xpm");
}

void	initialise_enemy_textures(t_vars *vars, t_img *animation,
							const char **frames)
{
	int	frame_count;

	frame_count = count_frames(frames);
	load_animated_sprite(vars, animation, frames, frame_count);
}
