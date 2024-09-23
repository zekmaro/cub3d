/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gunshot_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:54:34 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/09 23:58:33 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_dim	calculate_scaled_dimensions(t_img *image, double scale)
{
	t_dim	dimensions;

	dimensions.width = image->width * scale;
	dimensions.height = image->height * scale;
	return (dimensions);
}

t_dim	calculate_screen_start_position(t_vars *vars, t_dim scaled_dimensions, \
			int offset_x, int offset_y)
{
	t_dim	start_position;

	start_position.width = (vars->mlx->window_width / 2) \
		- (scaled_dimensions.width / 2) + offset_x;
	start_position.height = vars->mlx->window_height \
		- scaled_dimensions.height + offset_y;
	return (start_position);
}

void	draw_pixel(t_draw_params *params, t_scr_pos screen_pos, \
			t_tex_pos tex_pos)
{
	int	color;

	color = get_texture_color(params->image, tex_pos.x, tex_pos.y);
	if (color != -1)
		put_pixel_to_image(params->vars, params->screen_start.x + screen_pos.x,
			params->screen_start.y + screen_pos.y, color);
}

t_tex_pos	init_tex_pos(int x, int y)
{
	t_tex_pos	tex_pos;

	tex_pos.x = x;
	tex_pos.y = y;
	return (tex_pos);
}

t_scr_pos	init_scr_pos(int x, int y)
{
	t_scr_pos	scr_pos;

	scr_pos.x = x;
	scr_pos.y = y;
	return (scr_pos);
}
