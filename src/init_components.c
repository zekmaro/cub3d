/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_components.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:32:18 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/12 17:32:56 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialise_mlx(t_vars *vars)
{
	t_mlx	*mlx;

	vars->mlx = NULL;
	mlx = (t_mlx *)(malloc(sizeof(t_mlx)));
	if (!mlx)
	{
		vars->mlx = NULL;
		exit_with_error(vars, "Failed to allocate memory for mlx");
		exit(EXIT_FAILURE);
	}
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->window_height = 1080;
	mlx->window_width = 1920;
	vars->mlx = mlx;
}

void	initialise_line(t_vars *vars)
{
	t_line	*line;

	line = NULL;
	line = (t_line *)(malloc(sizeof(t_line)));
	if (!line)
	{
		vars->line = NULL;
		exit_with_error(vars, "Failed to allocate memory for line");
		exit(EXIT_FAILURE);
	}
	ft_bzero(line, sizeof(t_line));
	line->src_x = 1000;
	line->src_y = 300;
	vars->line = line;
}

void	initialise_image(t_vars *vars)
{
	t_img	*image;

	image = NULL;
	image = (t_img *)(malloc(sizeof(t_img)));
	if (!image)
	{
		vars->image = NULL;
		exit_with_error(vars, "Failed to allocate memory for image");
		exit(EXIT_FAILURE);
	}
	ft_bzero(image, sizeof(t_img));
	vars->image = image;
}

void	initialise_player(t_vars *vars)
{
	t_player	*player;

	player = NULL;
	player = (t_player *)(malloc(sizeof(t_player)));
	if (!player)
	{
		vars->player = NULL;
		exit_with_error(vars, "Failed to allocate memory for player");
		exit(EXIT_FAILURE);
	}
	ft_bzero(player, sizeof(t_player));
	player->player_size = 8;
	vars->player = player;
}

void	initialise_ray(t_vars *vars)
{
	t_ray	*ray;

	ray = NULL;
	ray = (t_ray *)(malloc(sizeof(t_ray)));
	if (!ray)
	{
		vars->ray = NULL;
		exit_with_error(vars, "Failed to allocate memory for ray");
		exit(EXIT_FAILURE);
	}
	ft_bzero(ray, sizeof(t_ray));
	vars->ray = ray;
}
