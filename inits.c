/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:32:18 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/24 14:11:24 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	vars->player = player;
}

void	initialise_vars(t_vars *vars)
{
	initialise_image(vars);
	initialise_map(vars);
	initialise_mlx(vars);
	initialise_line(vars);
	initialise_player(vars);
}