/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:22 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/10 15:03:17 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

// int	draw_sprite(t_vars *vars)
// {
// 	//update_sprite_frame(vars->animated_sprite);
// 	draw_map(vars);
// 	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
// 		vars->image->mlx_img, 0, 0);
// 	return (0);
// }
