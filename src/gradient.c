/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:10:20 by anarama           #+#    #+#             */
/*   Updated: 2024/09/09 21:06:27 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	apply_transparency(uint32_t color, double trans_coef)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	red = (color << 16) & 0xFF;
	green = (color << 8) & 0xFF;
	blue = color & 0xFF;
	alpha = (uint8_t)(trans_coef * 255);
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

uint32_t	combine_colors(uint32_t color1, uint32_t color2)
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
	return ((255 << 24) | r_blend | g_blend | b_blend);
}

void	blend_pixel_to_image(t_vars *vars, int x, int y, uint32_t color)
{
	uint32_t	original_color;
	uint32_t	blended_color;

	original_color = get_texture_color(vars->image, x, y);
	blended_color = combine_colors(original_color, color);
	put_pixel_to_image(vars, x, y, blended_color);
}

void	draw_player_damaged(t_vars *vars)
{
	int			screen_width;
	int			screen_height;
	int			center_x;
	int			center_y;
	double		max_distance;
	int			x;
	int			y;	
	double		distance;
	double		intensity;
	uint32_t	red_color;

	screen_width = vars->mlx->window_width;
	screen_height = vars->mlx->window_height;
	center_x = screen_width / 2;
	center_y = screen_height / 2;
	max_distance = sqrt(center_x * center_x + center_y * center_y);
	y = -1;
	while (++y < screen_height)
	{
		x = -1;
		while (++x < screen_width)
		{
			distance = sqrt((x - center_x) * (x - center_x) \
				+ (y - center_y) * (y - center_y));
			intensity = 1.0 - (distance / max_distance);
			if (intensity < 0)
				intensity = 0;
			red_color = apply_transparency(RED, intensity);
			blend_pixel_to_image(vars, x, y, red_color);
		}
	}
}
