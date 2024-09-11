/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:03:38 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/10 22:27:32 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_animated_sprite(t_vars *vars, t_img *sprite, \
		const char **file_paths, int frame_count)
{
	int		width;
	int		height;
	t_img	*tmp;
	int		i;

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
		sprite->frames[i] = mlx_xpm_file_to_image(vars->mlx->mlx, \
			(char *)file_paths[i], &width, &height);
		tmp = (t_img *)sprite->frames[i];
		if (!sprite->frames[i])
		{
			exit_with_error(vars, "Failed to load sprite frame");
			exit(EXIT_FAILURE);
		}
		tmp->addr = mlx_get_data_addr(\
			tmp, \
			&tmp->bits_per_pixel, \
			&tmp->line_len, \
			&tmp->endian);
		tmp->width = width;
		tmp->height = height;
	}
}

void	update_sprite_frame(t_img *sprite)
{
	sprite->current_frame = (sprite->current_frame + 1) % sprite->frame_count;
}

void	calculate_sprite_distances(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->num_sprites)
		vars->sprites[i].distance = sqrt(pow(vars->player->x \
		- vars->sprites[i].x, 2) + pow(vars->player->y \
		- vars->sprites[i].y, 2));
}

void	project_sprite(t_vars *vars, t_sprite *sprite)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;

	sprite_x = sprite->x - vars->player->x;
	sprite_y = sprite->y - vars->player->y;
	inv_det = 1.0 / (vars->player->plane_x * vars->player->dir_y \
		- vars->player->dir_x * vars->player->plane_y);
	transform_x = inv_det * (vars->player->dir_y * sprite_x \
		- vars->player->dir_x * sprite_y);
	transform_y = inv_det * (-vars->player->plane_y * sprite_x \
		+ vars->player->plane_x * sprite_y);
	sprite->screen_x = (int)((vars->mlx->window_width / 2) \
		* (1 + transform_x / transform_y));
	sprite->height = abs((int)(vars->mlx->window_height / transform_y));
	sprite->width = abs((int)(vars->mlx->window_height / transform_y));
}

void	sort_sprites(t_vars *vars)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = -1;
	while (++i < vars->num_sprites - 1)
	{
		j = i;
		while (++j < vars->num_sprites)
		{
			if (vars->sprites[i].distance < vars->sprites[j].distance)
			{
				temp = vars->sprites[i];
				vars->sprites[i] = vars->sprites[j];
				vars->sprites[j] = temp;
			}
		}
	}
}
// void	put_enemy_on_screen(t_vars *vars)
// {
// 	int	screen_x;
// 	int	screen_y;
//
// 	screen_x = (vars->map->monster_x * vars->unit_size) + vars->unit_size / 2;
// 	screen_y = (vars->map->monster_y * vars->unit_size) + vars->unit_size / 2;
// 	vars->animated_sprite->current_frame_ptr = 
// 		vars->animated_sprite->frames[vars->animated_sprite->current_frame];
// 	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, 
// 		vars->animated_sprite->current_frame_ptr, screen_x, screen_y);
// }
