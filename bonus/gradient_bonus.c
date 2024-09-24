/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:10:20 by anarama           #+#    #+#             */
/*   Updated: 2024/09/24 16:58:54 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static uint32_t	apply_transparency(uint32_t color, double trans_coef)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	red = (color << 16) & 0xFF;
	green = (color << 8) & 0xFF;
	blue = color & 0xFF;
	alpha = (uint8_t)(trans_coef * 255);
	return (((uint32_t)alpha << 24) | (red << 16) | (green << 8) | blue);
}

static uint32_t	combine_colors(uint32_t color1, uint32_t color2)
{
	uint32_t	alpha;
	uint32_t	result;
	uint32_t	r_blend;
	uint32_t	g_blend;
	uint32_t	b_blend;

	alpha = (color2 >> 24) & 0xFF;
	result = ((color1 >> 16) & 0xFF) * (255 - alpha)
		+ ((color2 >> 16) & 0xFF);
	r_blend = (result / 255) << 16;
	result = ((color1 >> 8) & 0xFF) * (255 - alpha)
		+ ((color2 >> 8) & 0xFF);
	g_blend = (result / 255) << 8;
	result = (color1 & 0xFF) * (255 - alpha)
		+ (color2 & 0xFF);
	b_blend = result / 255;
	return (((uint32_t)255 << 24) | r_blend | g_blend | b_blend);
}

static void	blend_pixel_to_image(t_vars *vars, int x, int y, uint32_t color)
{
	uint32_t	original_color;
	uint32_t	blended_color;

	original_color = get_texture_color(vars->image, x, y);
	blended_color = combine_colors(original_color, color);
	put_pixel_to_image(vars, x, y, blended_color);
}

static void	process_pixel(t_vars *vars, int x, int y, t_pixel_params *params)
{
	double		distance;
	double		intensity;
	uint32_t	red_color;

	distance = sqrt((x - params->center_x) * (x - params->center_x) \
					+ (y - params->center_y) * (y - params->center_y));
	intensity = 1.0 - (distance / params->max_distance);
	if (intensity < 0)
		intensity = 0;
	red_color = apply_transparency(RED, intensity);
	blend_pixel_to_image(vars, x, y, red_color);
}

void	draw_player_damaged(t_vars *vars)
{
	t_pixel_params	params;
	int				screen_width;
	int				screen_height;
	int				x;
	int				y;

	screen_width = vars->mlx->window_width;
	screen_height = vars->mlx->window_height;
	params.center_x = screen_width / 2;
	params.center_y = screen_height / 2;
	params.max_distance = sqrt(params.center_x * params.center_x \
							+ params.center_y * params.center_y);
	y = -1;
	while (++y < screen_height)
	{
		x = -1;
		while (++x < screen_width)
			process_pixel(vars, x, y, &params);
	}
}
