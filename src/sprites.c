/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:03:38 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/01 15:59:42 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>

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

void	put_enemy_on_screen(t_vars *vars)
{
	int	screen_x;
	int	screen_y;

	screen_x = (vars->map->monster_x * vars->unit_size) + vars->unit_size / 2;
	screen_y = (vars->map->monster_y * vars->unit_size) + vars->unit_size / 2;
	vars->animated_sprite->current_frame_ptr = \
		vars->animated_sprite->frames[vars->animated_sprite->current_frame];
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, \
		vars->animated_sprite->current_frame_ptr, screen_x, screen_y);
}

int	draw_sprite(t_vars *vars)
{
	long	elapsed_time;

	get_current_time(&vars->current_time);
	elapsed_time = get_elapsed_time(&vars->program_start, &vars->current_time);
	if (elapsed_time % 200 == 0)
	{
		update_sprite_frame(vars->animated_sprite);
		put_enemy_on_screen(vars);
	}
	return (0);
}
