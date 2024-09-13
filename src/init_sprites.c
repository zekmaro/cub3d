/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:19:28 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 02:37:04 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialise_enemy_textures(t_vars *vars, t_img *animation,
							const char **frames)
{
	int	frame_count;

	frame_count = count_frames(frames);
	load_animated_sprite(vars, animation, frames, frame_count);
}

void	load_sprite_texture(t_vars *vars, t_img *sprite_texture, \
			const char *file_path)
{
	int	width;
	int	height;

	sprite_texture->mlx_img = mlx_xpm_file_to_image(vars->mlx->mlx, \
		(char *)file_path, &width, &height);
	if (!sprite_texture->mlx_img)
	{
		perror("Failed to load sprite texture");
		free_and_exit(vars);
	}
	sprite_texture->addr = mlx_get_data_addr(sprite_texture->mlx_img, \
		&sprite_texture->bits_per_pixel, &sprite_texture->line_len, \
		&sprite_texture->endian);
	if (!sprite_texture->addr)
	{
		perror("Failed to get sprite texture data address");
		free_and_exit(vars);
	}
	sprite_texture->width = width;
	sprite_texture->height = height;
}

void	initialise_sprites(t_vars *vars)
{
	vars->num_sprites = 1;
	vars->sprites = ft_calloc(sizeof(t_sprite), vars->num_sprites);
	if (!vars->sprites)
	{
		perror("Failed to allocate memory for sprites");
		free_and_exit(vars);
	}
	const char *gun_frames[] \
	= {
		"./assets/gun1.xpm",
		"./assets/gun2.xpm",
		"./assets/gun3.xpm",
		"./assets/gun4.xpm"
	};
	const char *fire_frames[] \
	= {
		"./assets/gunfire1.xpm",
		"./assets/gunfire2.xpm",
	};
	const char *door_frames[] \
	= {
		"./assets/door0.xpm",
		"./assets/door1.xpm",
		"./assets/door2.xpm",
		"./assets/door3.xpm",
	};
	vars->player->gun = ft_calloc(sizeof(t_img), 1);
	if (!vars->player->gun)
	{
		perror("Failed to allocate memory for gun sprite");
		free_and_exit(vars);
	}
	vars->player->fire = ft_calloc(sizeof(t_img), 1);
	if (!vars->player->fire)
	{
		perror("Failed to allocate memory for fire sprite");
		free_and_exit(vars);
	}
	vars->door->textures = ft_calloc(sizeof(t_img), 1);
	if (!vars->door->textures)
	{
		perror("Failed to allocate memory for door textures");
		free_and_exit(vars);
	}
	load_animated_sprite(vars, vars->player->gun, gun_frames, 4);
	load_animated_sprite(vars, vars->player->fire, fire_frames, 2);
	load_animated_sprite(vars, vars->door->textures, door_frames, 4);
}
