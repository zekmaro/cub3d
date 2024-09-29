/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:19:28 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/29 15:45:52 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_sprite_texture(t_vars *vars, t_img *sprite_texture, \
			const char *file_path)
{
	int	width;
	int	height;

	if (!vars || !sprite_texture || !file_path)
		return ;
	sprite_texture->mlx_img = mlx_xpm_file_to_image(vars->mlx->mlx, \
		(char *)file_path, &width, &height);
	if (!sprite_texture->mlx_img)
	{
		ft_putstr_fd("Error\nFailed to load sprite texture\n", 2);
		free_and_exit(vars);
	}
	sprite_texture->addr = mlx_get_data_addr(sprite_texture->mlx_img, \
		&sprite_texture->bits_per_pixel, &sprite_texture->line_len, \
		&sprite_texture->endian);
	if (!sprite_texture->addr)
	{
		exit_with_error(vars, \
			"Error\nFailed to get sprite texture data address\n");
	}
	sprite_texture->width = width;
	sprite_texture->height = height;
}

void	allocate_sprite_memory(t_vars *vars, t_img **sprite, \
			const char *error_message)
{
	*sprite = ft_calloc(sizeof(t_img), 1);
	if (!*sprite)
	{
		ft_putstr_fd((char *)error_message, 2);
		free_and_exit(vars);
	}
}

void	allocate_memory_for_sprites(t_vars *vars)
{
	if (vars == NULL)
		return ;
	vars->num_sprites = 1;
	vars->sprites = ft_calloc(sizeof(t_sprite), vars->num_sprites);
	if (!vars->sprites)
	{
		ft_putstr_fd("Error\nFailed to allocate memory for sprites\n", 2);
		free_and_exit(vars);
	}
}

void	load_sprites(t_vars *vars)
{
	const char	*gun_frames[] = {"./assets/gun1.xpm", \
		"./assets/gun2.xpm", "./assets/gun3.xpm", "./assets/gun4.xpm"};
	const char	*fire_frames[] = {"./assets/gunfire1.xpm", \
		"./assets/gunfire2.xpm"};
	const char	*door_frames[] = {"./assets/door0.xpm", \
		"./assets/door1.xpm", "./assets/door2.xpm", "./assets/door3.xpm"};

	if (vars == NULL)
		return ;
	/*
	allocate_sprite_memory(vars, &vars->player->gun, \
		"Error\nFailed to allocate memory for gun sprite\n");
	allocate_sprite_memory(vars, &vars->player->fire, \
		"Error\nFailed to allocate memory for fire sprite\n");
	*/
	load_animated_sprite(vars, vars->player->gun, gun_frames, 4);
	load_animated_sprite(vars, vars->player->fire, fire_frames, 2);
	if (vars->doors == NULL)
		return ;
	/*
	allocate_sprite_memory(vars, &vars->doors->textures, \
		"Error\nFailed to allocate memory for door textures\n");
	*/
	load_animated_sprite(vars, vars->doors->textures, door_frames, 4);
}

void	initialise_sprites(t_vars *vars)
{
	if (vars == NULL)
		return ;
	allocate_memory_for_sprites(vars);
	load_sprites(vars);
}
