/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:12:34 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/24 17:00:55 by iberegsz         ###   ########.fr       */
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
		ft_putstr_fd("Error\nFailed to load texture\n", 2);
		free_and_exit(vars);
	}
	vars->textures[texture_index]->addr = mlx_get_data_addr(\
		vars->textures[texture_index], \
		&vars->textures[texture_index]->bits_per_pixel, \
		&vars->textures[texture_index]->line_len, \
		&vars->textures[texture_index]->endian);
	if (!vars->textures[texture_index]->addr)
	{
		ft_putstr_fd("Error\nFailed to get texture data address\n", 2);
		free_and_exit(vars);
	}
	vars->textures[texture_index]->width = width;
	vars->textures[texture_index]->height = height;
}

void	initialise_textures(t_vars *vars)
{
	int	i;

	if (!vars->mlx || !vars->mlx->mlx)
		exit_with_error(vars, "Error\nMLX not initialized\n");
	i = -1;
	while (++i < 4)
	{
		if (!vars->texture_names[i])
			exit_with_error(vars, \
				"Error\nTexture names memory allocation error\n");
		load_texture(vars, i, vars->texture_names[i]);
	}
	load_texture(vars, TEXTURE_DOOR0, "./assets/door0.xpm");
	load_texture(vars, TEXTURE_DOOR1, "./assets/door0.xpm");
	load_texture(vars, TEXTURE_DOOR2, "./assets/door0.xpm");
	load_texture(vars, TEXTURE_DOOR3, "./assets/door0.xpm");
}

void	initialise_enemy_textures(t_vars *vars, t_img *animation,
							const char **frames)
{
	int	frame_count;

	if (!vars || !animation || !frames)
		return ;
	frame_count = count_frames(frames);
	load_animated_sprite(vars, animation, frames, frame_count);
}
