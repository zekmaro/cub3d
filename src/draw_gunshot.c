/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gunshot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:39:25 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/14 15:23:28 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_draw_params	init_draw_params(t_draw_image_params *params, \
					t_dim screen_start_position)
{
	t_draw_params	draw_params;

	draw_params.vars = params->vars;
	draw_params.image = params->image;
	draw_params.screen_start.x = screen_start_position.width;
	draw_params.screen_start.y = screen_start_position.height;
	draw_params.scale = params->scale;
	return (draw_params);
}

void	draw_row(t_draw_params *draw_params, t_tex_pos *tex_pos, int screen_y, \
			int scaled_width)
{
	int	screen_x;

	screen_x = 0;
	while (screen_x < scaled_width)
	{
		tex_pos->x = screen_x / draw_params->scale;
		draw_pixel(draw_params, init_scr_pos(screen_x, screen_y), *tex_pos);
		screen_x++;
	}
}

void	draw_scaled_image(t_draw_image_params *params)
{
	t_dim			scaled_dimensions;
	t_dim			screen_start_position;
	t_draw_params	draw_params;
	t_tex_pos		tex_pos;
	int				screen_y;

	screen_y = 0;
	scaled_dimensions = calculate_scaled_dimensions(params->image, \
		params->scale);
	screen_start_position = calculate_screen_start_position(params->vars, \
		scaled_dimensions, params->offset_x, params->offset_y);
	draw_params = init_draw_params(params, screen_start_position);
	tex_pos = init_tex_pos(0, screen_y / params->scale);
	while (screen_y < scaled_dimensions.height)
	{
		tex_pos = init_tex_pos(0, screen_y / params->scale);
		draw_row(&draw_params, &tex_pos, screen_y, scaled_dimensions.width);
		screen_y++;
	}
}

void	draw_fire(t_vars *vars, double scale)
{
	t_img				*temp;
	t_draw_image_params	params;

	temp = \
		(t_img *)vars->player->fire->frames[vars->player->fire->current_frame];
	params.vars = vars;
	params.image = temp;
	params.scale = scale;
	params.offset_x = 18;
	params.offset_y = -250;
	draw_scaled_image(&params);
}

void	draw_gun(t_vars *vars, double scale)
{
	t_img				*temp;
	t_draw_image_params	params;

	temp = \
		(t_img *)vars->player->gun->frames[vars->player->gun->current_frame];
	params.vars = vars;
	params.image = temp;
	params.scale = scale;
	params.offset_x = 0;
	params.offset_y = -100;
	draw_scaled_image(&params);
}
