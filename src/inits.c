/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:32:18 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/04 01:29:18 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialise_mlx(t_vars *vars)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)(malloc(sizeof(t_mlx)));
	if (!mlx)
	{
		cleanup_vars(vars);
	}
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->window_height = 1080;
	mlx->window_width = 1920;
	vars->mlx = mlx;
}

void	initialise_line(t_vars *vars)
{
	t_line	*line;

	line = (t_line *)(malloc(sizeof(t_line)));
	if (!line)
	{
		cleanup_vars(vars);
	}
	ft_bzero(line, sizeof(t_line));
	line->src_x = 1000;
	line->src_y = 300;
	vars->line = line;
}

void	initialise_image(t_vars *vars)
{
	t_img	*image;

	image = (t_img *)(malloc(sizeof(t_img)));
	if (!image)
	{
		cleanup_vars(vars);
	}
	ft_bzero(image, sizeof(t_img));
	vars->image = image;
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

void	initialise_player(t_vars *vars)
{
	t_player	*player;

	player = (t_player *)(malloc(sizeof(t_player)));
	if (!player)
	{
		cleanup_vars(vars);
	}
	ft_bzero(player, sizeof(t_player));
	player->player_size = 8;
	vars->player = player;
}

void	initialise_ray(t_vars *vars)
{
	t_ray	*ray;

	ray = (t_ray *)(malloc(sizeof(t_ray)));
	if (!ray)
	{
		cleanup_vars(vars);
	}
	ft_bzero(ray, sizeof(t_ray));
	vars->ray = ray;
}

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

void load_sprite_texture(t_vars *vars, t_img *sprite_texture, const char *file_path)
{
    int width;
    int height;

    sprite_texture->mlx_img = mlx_xpm_file_to_image(vars->mlx->mlx, (char *)file_path, &width, &height);
    if (!sprite_texture->mlx_img)
    {
        perror("Failed to load sprite texture");
        free_and_exit(vars);
    }
    sprite_texture->addr = mlx_get_data_addr(sprite_texture->mlx_img, &sprite_texture->bits_per_pixel, &sprite_texture->line_len, &sprite_texture->endian);
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
    vars->sprite_texture = ft_calloc(sizeof(t_img), 1);
    if (!vars->sprite_texture)
    {
        perror("Failed to allocate memory for sprite texture");
        free_and_exit(vars);
    }
    load_sprite_texture(vars, vars->sprite_texture, "./assets/lamp.xpm");
	const char *sprite_frames[] \
	= {
		"./assets/tile000.xpm",
		"./assets/tile001.xpm",
		"./assets/tile002.xpm",
		"./assets/tile003.xpm"
	};
	const char *gun_frames[] \
	= {
		"./assets/gun1.xpm",
		"./assets/gun2.xpm",
		"./assets/gun3.xpm",
		"./assets/gun4.xpm"
	};
	vars->animated_sprite = ft_calloc(sizeof(t_img), 1);
	if (!vars->animated_sprite)
	{
		perror("Failed to allocate memory for animated sprite");
		free_and_exit(vars);
	}
	vars->player->gun = ft_calloc(sizeof(t_img), 1);
	if (!vars->player->gun)
	{
		perror("Failed to allocate memory for gun sprite");
		free_and_exit(vars);
	}
	load_animated_sprite(vars, vars->animated_sprite, sprite_frames, 4);
	load_animated_sprite(vars, vars->player->gun, gun_frames, 4);
}

void	initialise_zbuffer(t_vars *vars)
{
	vars->zbuffer = malloc(sizeof(int) * vars->mlx->window_width);
	if (!vars->zbuffer)
	{
		perror("Failed to allocate memory for zbuffer");
		free_and_exit(vars);
	}
}

void	initialise_vars(t_vars *vars)
{
	vars->unit_size = 64;
	ft_bzero(vars->textures, sizeof(vars->textures));
	initialise_image(vars);
	initialise_map(vars);
	initialise_mlx(vars);
	initialise_line(vars);
	initialise_ray(vars);
	initialise_player(vars);	
	initialise_zbuffer(vars);
}
