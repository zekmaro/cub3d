/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:52:59 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/02 11:59:16 by iberegsz         ###   ########.fr       */
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
}

void	initialise_textures(t_vars *vars)
{
	if (!vars->mlx || !vars->mlx->mlx)
	{
		perror("MLX not initialized");
		free_and_exit(vars);
	}
	load_texture(vars, TEXTURE_NORTH, "./assets/north_texture.xpm");
	load_texture(vars, TEXTURE_SOUTH, "./assets/south_texture.xpm");
	load_texture(vars, TEXTURE_WEST, "./assets/west_texture.xpm");
	load_texture(vars, TEXTURE_EAST, "./assets/east_texture.xpm");
}

void	initialise_sprites(t_vars *vars)
{
	const char *sprite_frames[] \
	= {
		"./assets/tile000.xpm",
		"./assets/tile001.xpm",
		"./assets/tile002.xpm",
		"./assets/tile003.xpm"
	};
	vars->animated_sprite = malloc(sizeof(t_img));
	if (!vars->animated_sprite)
	{
		perror("Failed to allocate memory for animated sprite");
		free_and_exit(vars);
	}
	load_animated_sprite(vars, vars->animated_sprite, sprite_frames, 4);
}

void	initialise_map(t_vars *vars)
{
	t_map	*map;

	map = (t_map *)(malloc(sizeof(t_map)));
	if (!map)
	{
		cleanup_vars(vars);
	}
	ft_bzero(map, sizeof(t_map));
	vars->map = map;
}

void	initialise_vars(t_vars *vars)
{
	int	i;

	vars->unit_size = 16;
	i = -1;
	while (++i < 4)
		vars->textures[i] = NULL;
	initialise_image(vars);
	initialise_map(vars);
	initialise_mlx(vars);
	initialise_line(vars);
	initialise_ray(vars);
	initialise_player(vars);
}
