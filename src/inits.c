/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:32:18 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/30 23:53:50 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialise_mlx(t_vars *vars)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)(malloc(sizeof(t_mlx)));
	if (!mlx)
	{
		//cleanup_vars(vars);
		exit (1);
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
		//cleanup_vars(vars);
		exit (1);
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
		//cleanup_vars(vars);
		exit (1);
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
		//cleanup_vars(vars);
		exit (1);
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
		//cleanup_vars(vars);
		exit (1);
	}
	ft_bzero(player, sizeof(t_player));
	player->player_size = 8;
	vars->player = player;
}

void	initialise_textures(t_vars *vars)
{
	int	width;
	int	height;
	int	i;

	if (!vars->mlx || !vars->mlx->mlx)
	{
		perror("MLX not initialized");
		free_and_exit(vars);
	}
	vars->textures[0] = mlx_xpm_file_to_image(vars->mlx->mlx, \
		"./assets/north_texture.xpm", &width, &height);
	vars->textures[1] = mlx_xpm_file_to_image(vars->mlx->mlx, \
		"./assets/south_texture.xpm", &width, &height);
	vars->textures[2] = mlx_xpm_file_to_image(vars->mlx->mlx, \
		"./assets/west_texture.xpm", &width, &height);
	vars->textures[3] = mlx_xpm_file_to_image(vars->mlx->mlx, \
		"./assets/east_texture.xpm", &width, &height);
	if (!vars->textures[0] || !vars->textures[1] \
		|| !vars->textures[2] || !vars->textures[3])
	{
		perror("Failed to load textures");
		free_and_exit(vars);
	}
	i = -1;
	while (++i < 4)
	{
		vars->textures[i]->addr = mlx_get_data_addr(vars->textures[i], \
			&vars->textures[i]->bits_per_pixel, &vars->textures[i]->line_len, \
			&vars->textures[i]->endian);
		if (!vars->textures[i]->addr)
		{
			perror("Failed to get texture data address");
			free_and_exit(vars);
		}
	}
}

void	initialise_vars(t_vars *vars)
{
	int	i;

	vars->unit_size = 32;
	i = -1;
	while (++i < 4)
		vars->textures[i] = NULL;
	initialise_image(vars);
	initialise_map(vars);
	initialise_mlx(vars);
	initialise_line(vars);
	initialise_player(vars);
}
