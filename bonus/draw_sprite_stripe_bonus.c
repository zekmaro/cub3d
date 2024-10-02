/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_stripe_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:50:17 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/30 03:32:15 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	calculate_tex_x(t_sprite_params *params, t_img *tmp, int stripe)
{
	return ((int)(256 * (stripe - (-params->sprite_width / 2 \
		+ params->sprite_screen_x)) * tmp->width / params->sprite_width) \
		/ 256);
}

static int	calculate_tex_y(t_img *tmp, t_vars *vars, \
				t_sprite_params *params, int y)
{
	int	d;

	d = (y - vars->mlx->window_height / 2 + params->sprite_height / 2) * 256;
	return (((d * tmp->height) / params->sprite_height) / 256);
}

static void	draw_raycaster_pixel(t_vars *vars, int stripe, int y, int color)
{
	if (color != -1)
	{
		put_pixel_to_image(vars, stripe, y + 50, color);
	}
}

static void	update_zbuffer(t_vars *vars, int stripe, double transform_y, \
				int color)
{
	if (color != -1)
	{
		vars->zbuffer[stripe] = transform_y;
	}
}

void	draw_sprite_stripe(t_vars *vars, t_sprite_params *params, \
			t_sprite_calc_params *calc_params, t_img *tmp)
{
	int	stripe;
	int	tex_x;
	int	tex_y;
	int	y;
	int	color;

	stripe = params->draw_start_x - 1;
	while (++stripe < params->draw_end_x)
	{
		tex_x = calculate_tex_x(params, tmp, stripe);
		if (calc_params->transform_y > 0 && stripe > 0 \
			&& stripe < vars->mlx->window_width \
			&& calc_params->transform_y < vars->zbuffer[stripe])
		{
			y = params->draw_start_y - 1;
			while (++y < params->draw_end_y)
			{
				tex_y = calculate_tex_y(tmp, vars, params, y);
				color = get_texture_color(vars, tmp, tex_x, tex_y);
				draw_raycaster_pixel(vars, stripe, y, color);
				update_zbuffer(vars, stripe, calc_params->transform_y, color);
			}
		}
	}
}
