/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:22 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/18 20:39:48 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_draw_limits(t_vars *vars, t_sprite *sprite, \
		t_draw_limits *limits)
{
	limits->draw_start_y = -sprite->height / 2 + vars->mlx->window_height / 2;
	if (limits->draw_start_y < 0)
		limits->draw_start_y = 0;
	limits->draw_end_y = sprite->height / 2 + vars->mlx->window_height / 2;
	if (limits->draw_end_y >= vars->mlx->window_height)
		limits->draw_end_y = vars->mlx->window_height - 1;
	limits->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	if (limits->draw_start_x < 0)
		limits->draw_start_x = 0;
	limits->draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (limits->draw_end_x >= vars->mlx->window_width)
		limits->draw_end_x = vars->mlx->window_width - 1;
}

void	draw_sprites_stripe(t_vars *vars, t_sprite *sprite, int stripe, \
			t_draw_limits *limits)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	if (sprite->distance < vars->zbuffer[stripe])
	{
		y = limits->draw_start_y;
		while (y < limits->draw_end_y)
		{
			tex_x = (int)((stripe - (-sprite->width / 2 + sprite->screen_x)) \
				* vars->sprite_texture->width / sprite->width);
			tex_y = (int)((y - (-sprite->height / 2 + vars->mlx->window_height \
				/ 2)) * vars->sprite_texture->height / sprite->height);
			color = get_texture_color(vars->sprite_texture, tex_x, tex_y);
			if (color != -1)
				put_pixel_to_image(vars, stripe, y, color);
			y++;
		}
	}
}

void	draw_sprites(t_vars *vars)
{
	int				i;
	int				stripe;
	t_draw_limits	limits;

	calculate_sprite_distances(vars);
	sort_sprites(vars);
	i = 0;
	while (i < vars->num_sprites)
	{
		project_sprite(vars, &vars->sprites[i]);
		calculate_draw_limits(vars, &vars->sprites[i], &limits);
		stripe = limits.draw_start_x;
		while (stripe < limits.draw_end_x)
		{
			draw_sprites_stripe(vars, &vars->sprites[i], stripe, &limits);
			stripe++;
		}
		i++;
	}
}
