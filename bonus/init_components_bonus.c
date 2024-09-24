/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_components_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:32:18 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/24 17:00:03 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialise_line(t_vars *vars)
{
	t_line	*line;

	line = (t_line *)(malloc(sizeof(t_line)));
	if (!line)
	{
		exit_with_error(vars, \
			"Error\nFailed to allocate memory for line\n");
		return ;
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
		exit_with_error(vars, "Error\nFailed to allocate memory for image\n");
		return ;
	}
	ft_bzero(image, sizeof(t_img));
	vars->image = image;
}

void	initialise_player(t_vars *vars)
{
	t_player	*player;

	player = (t_player *)(malloc(sizeof(t_player)));
	if (!player)
	{
		exit_with_error(vars, "Error\nFailed to allocate memory for player\n");
		return ;
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
		exit_with_error(vars, "Error\nFailed to allocate memory for ray\n");
		return ;
	}
	ft_bzero(ray, sizeof(t_ray));
	vars->ray = ray;
}
