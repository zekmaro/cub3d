/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:19:28 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/11 14:56:26 by anarama          ###   ########.fr       */
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

// void	init_imp_sprites(t_vars *vars, t_enemy *imp)
// {
// 	const char *imp_movement_frames[] \
// 	= {
// 		"./assets/imp_walk1.xpm",
// 		"./assets/imp_walk2.xpm",
// 		"./assets/imp_walk3.xpm",
// 		"./assets/imp_walk4.xpm",
// 		NULL
// 	};
// 	const char *imp_death_frames[] \
// 	= {
// 		"./assets/imp_dies1.xpm",
// 		"./assets/imp_dies2.xpm",
// 		"./assets/imp_dies3.xpm",
// 		"./assets/imp_dies4.xpm",
// 		"./assets/imp_dies5.xpm",
// 		NULL
// 	};
// 	const char *imp_attack_frames[] \
// 	= {
// 		"./assets/imp_attack1.xpm",
// 		"./assets/imp_attack2.xpm",
// 		"./assets/imp_attack3.xpm",
// 		NULL
// 	};
// 	const char *imp_fire_ball_frames[] \
// 	= {
// 		"./assets/imp_fire1.xpm",
// 		"./assets/imp_fire2.xpm",
// 		NULL
// 	};
// 	initialise_enemy_textures(vars, imp->move_animation, imp_movement_frames);
// 	initialise_enemy_textures(vars, imp->death_animation, imp_death_frames);
// 	initialise_enemy_textures(vars, imp->attack_animation, imp_attack_frames);
// 	initialise_enemy_textures(vars, imp->fire_ball, imp_fire_ball_frames);
// 	imp->current_animation = imp->move_animation;
// }

// void	init_caco_sprites(t_vars *vars, t_enemy *caco)
// {
// 	(void)vars;
// 	const char *caco_movement_frames[] \
// 	= {
// 		"./assets/cacodemon1.xpm",
// 		"./assets/caco_walk1.xpm",
// 		"./assets/caco_walk2.xpm",
// 		"./assets/caco_walk3.xpm",
// 		"./assets/caco_walk4.xpm",
// 		"./assets/caco_walk5.xpm",
// 		"./assets/caco_walk6.xpm",
// 		NULL
// 	};
// 	const char *caco_death_frames[] \
// 	= {
// 		"./assets/caco_dies1.xpm",
// 		"./assets/caco_dies2.xpm",
// 		"./assets/caco_dies3.xpm",
// 		"./assets/caco_dies4.xpm",
// 		"./assets/caco_dies5.xpm",
// 		NULL
// 	};
// 	const char *caco_attack_frames[] \
// 	= {
// 		"./assets/cacodemon2.xpm",
// 		"./assets/cacodemon3.xpm",
// 		"./assets/cacodemon4.xpm",
// 		NULL
// 	};
// 	const char *caco_fire_ball_frames[] \
// 	= {
// 		"./assets/caco_fire1.xpm",
// 		NULL
// 	};
// 	initialise_enemy_textures(vars, caco->move_animation, caco_movement_frames);
// 	initialise_enemy_textures(vars, caco->death_animation, caco_death_frames);
// 	initialise_enemy_textures(vars, caco->attack_animation, caco_attack_frames);
// 	initialise_enemy_textures(vars, caco->fire_ball, caco_fire_ball_frames);
// 	caco->current_animation = caco->move_animation;
// }

void	initialise_sprites(t_vars *vars)
{
	vars->num_sprites = 1;
	vars->sprites = ft_calloc(sizeof(t_sprite), vars->num_sprites);
	if (!vars->sprites)
	{
		perror("Failed to allocate memory for sprites");
		free_and_exit(vars);
	}
	// vars->sprite_texture = ft_calloc(sizeof(t_img), 1);
	// if (!vars->sprite_texture)
	// {
	// 	perror("Failed to allocate memory for sprite texture");
	// 	free_and_exit(vars);
	// }
	// load_sprite_texture(vars, vars->sprite_texture, "./assets/lamp.xpm");
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
	// init_imp_sprites(vars);
	// init_caco_sprites(vars);
	load_animated_sprite(vars, vars->player->gun, gun_frames, 4);
	load_animated_sprite(vars, vars->player->fire, fire_frames, 2);
	load_animated_sprite(vars, vars->door->textures, door_frames, 4);
}
