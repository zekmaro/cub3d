/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:03:38 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/09 13:33:21 by iberegsz         ###   ########.fr       */
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
		perror("Failed to allocate memory for sprite frames");
		free_and_exit(vars);
	}
	i = -1;
	while (++i < frame_count)
	{
		sprite->frames[i] = mlx_xpm_file_to_image(vars->mlx->mlx, \
			(char *)file_paths[i], &width, &height);
		tmp = (t_img *)sprite->frames[i];
		tmp->addr = mlx_get_data_addr(\
		tmp, \
		&tmp->bits_per_pixel, \
		&tmp->line_len, \
		&tmp->endian);
		if (!sprite->frames[i])
		{
			perror("Failed to load sprite frame");
			free_and_exit(vars);
		}
		tmp->width = width;
		tmp->height = height;
	}
}

void	update_sprite_frame(t_img *sprite)
{
	sprite->current_frame = (sprite->current_frame + 1) % sprite->frame_count;
}

// void	put_enemy_on_screen(t_vars *vars)
// {
// 	int	screen_x;
// 	int	screen_y;

// 	screen_x = (vars->map->monster_x * vars->unit_size) + vars->unit_size / 2;
// 	screen_y = (vars->map->monster_y * vars->unit_size) + vars->unit_size / 2;
// 	vars->animated_sprite->current_frame_ptr = \
// 		vars->animated_sprite->frames[vars->animated_sprite->current_frame];
// 	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, \
// 		vars->animated_sprite->current_frame_ptr, screen_x, screen_y);
// }

int	draw_sprite(t_vars *vars)
{
	//update_sprite_frame(vars->animated_sprite);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
		vars->image->mlx_img, 0, 0);
	return (0);
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

void	draw_sprites(t_vars *vars)
{
	int	i;
	int	draw_start_y;
	int	draw_end_y;
	int	draw_start_x;
	int	draw_end_x;
	int	stripe;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	i = 0;
	calculate_sprite_distances(vars);
	sort_sprites(vars);
	i = 0;
	while (i < vars->num_sprites)
	{
		project_sprite(vars, &vars->sprites[i]);
		draw_start_y = -vars->sprites[i].height / 2 \
			+ vars->mlx->window_height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = vars->sprites[i].height / 2 + vars->mlx->window_height / 2;
		if (draw_end_y >= vars->mlx->window_height)
			draw_end_y = vars->mlx->window_height - 1;
		draw_start_x = -vars->sprites[i].width / 2 + vars->sprites[i].screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = vars->sprites[i].width / 2 + vars->sprites[i].screen_x;
		if (draw_end_x >= vars->mlx->window_width)
			draw_end_x = vars->mlx->window_width - 1;
		stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			if (vars->sprites[i].distance < vars->zbuffer[stripe])
			{
				y = draw_start_y;
				while (y < draw_end_y)
				{
					tex_x = (int)((stripe - (-vars->sprites[i].width / 2 \
						+ vars->sprites[i].screen_x)) \
						* vars->sprite_texture->width / vars->sprites[i].width);
					tex_y = (int)((y - (-vars->sprites[i].height / 2 \
						+ vars->mlx->window_height / 2)) \
						* vars->sprite_texture->height \
						/ vars->sprites[i].height);
					color = get_texture_color(vars->sprite_texture, \
						tex_x, tex_y);
					if (color != -1)
						put_pixel_to_image(vars, stripe, y, color);
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}
