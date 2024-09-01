/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:03:38 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/01 01:32:24 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_animated_sprite(t_vars *vars, t_img *sprite, \
		const char **file_paths, int frame_count)
{
	int	width;
	int	height;
	int	i;

	sprite->frame_count = frame_count;
	sprite->current_frame = 0;
	sprite->frames = malloc(sizeof(void *) * frame_count);
	if (!sprite->frames)
	{
		perror("Failed to allocate memory for sprite frames");
		free_and_exit(vars);
	}
	i = 0;
	while (i < frame_count)
	{
		sprite->frames[i] = mlx_xpm_file_to_image(vars->mlx->mlx, \
			(char *)file_paths[i], &width, &height);
		if (!sprite->frames[i])
		{
			perror("Failed to load sprite frame");
			free_and_exit(vars);
		}
		i++;
	}
}

void	update_sprite_frame(t_img *sprite)
{
	sprite->current_frame = (sprite->current_frame + 1) % sprite->frame_count;
}

void	draw_sprite(t_vars *vars, t_img *sprite, int x, int y)
{
	void	*current_frame;

	current_frame = sprite->frames[sprite->current_frame];
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, \
		current_frame, x, y);
}
