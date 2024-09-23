/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_animated_sprite.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:15:51 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/21 15:22:37 by iberegsz         ###   ########.fr       */
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

int	allocate_sprite_frames(t_vars *vars, t_img *sprite, int frame_count)
{
	sprite->frame_count = frame_count;
	sprite->current_frame = 0;
	sprite->frames = malloc(sizeof(void *) * frame_count);
	if (!sprite->frames)
	{
		exit_with_error(vars, \
			"Error\nFailed to allocate memory for sprite frames\n");
		return (1);
	}
	return (0);
}

int	load_single_frame(t_vars *vars, t_img *sprite, \
		const char *file_path, int index)
{
	int	width;
	int	height;

	sprite->frames[index] = load_sprite_frame(vars, file_path, \
		&width, &height);
	if (!sprite->frames[index])
	{
		cleanup_sprite_frames(vars, (t_img **)sprite->frames, index);
		exit_with_error(vars, "Error\nFailed to load sprite frame\n");
		return (1);
	}
	return (0);
}

void	load_animated_sprite(t_vars *vars, t_img *sprite, \
			const char **file_paths, int frame_count)
{
	int	i;

	if (vars == NULL || sprite == NULL || file_paths == NULL)
		return ;
	if (allocate_sprite_frames(vars, sprite, frame_count) != 0)
		return ;
	i = 0;
	while (i < frame_count)
	{
		if (load_single_frame(vars, sprite, file_paths[i], i) != 0)
			return ;
		i++;
	}
}
