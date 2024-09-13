/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_animated_sprite.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:15:51 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 14:15:57 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cleanup_sprite_frames(t_vars *vars, t_img **frames, int frame_count)
{
	t_img	*tmp;
	int		i;

	i = -1;
	while (++i < frame_count)
	{
		if (frames[i])
		{
			tmp = (t_img *)frames[i];
			mlx_destroy_image(vars->mlx->mlx, tmp->mlx_img);
			frames[i] = NULL;
		}
	}
	free(frames);
}

t_img	*load_sprite_frame(t_vars *vars, const char *file_path, \
			int *width, int *height)
{
	t_img	*frame;

	frame = (t_img *)mlx_xpm_file_to_image(vars->mlx->mlx, (char *)file_path, \
				width, height);
	if (!frame)
		return (NULL);
	frame->addr = mlx_get_data_addr(frame, &frame->bits_per_pixel, \
					&frame->line_len, &frame->endian);
	frame->width = *width;
	frame->height = *height;
	return (frame);
}

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
		exit_with_error(vars, "Failed to allocate memory for sprite frames");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < frame_count)
	{
		sprite->frames[i] = load_sprite_frame(vars, file_paths[i], \
								&width, &height);
		if (!sprite->frames[i])
		{
			cleanup_sprite_frames(vars, (t_img **)sprite->frames, i);
			exit_with_error(vars, "Failed to load sprite frame");
			exit(EXIT_FAILURE);
		}
	}
}
