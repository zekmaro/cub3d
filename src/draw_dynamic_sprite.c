/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dynamic_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 00:03:27 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 16:50:33 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_sprite_params(t_vars *vars, t_sprite_calc_params \
			*calc_params, t_sprite_params *params)
{
	double	screen_width;
	double	screen_height;

	screen_width = (double)vars->mlx->window_width;
	screen_height = (double)vars->mlx->window_height;
	params->sprite_screen_x = (int)((screen_width / 2.0) * (1.0 \
		+ calc_params->transform_x / calc_params->transform_y));
	params->sprite_height = abs((int)(screen_height * calc_params->scale \
		/ calc_params->transform_y));
	params->sprite_width = abs((int)(screen_height * calc_params->scale \
		/ calc_params->transform_y));
	params->draw_start_y = -params->sprite_height / 2 \
		+ vars->mlx->window_height / 2;
	if (params->draw_start_y < 0)
		params->draw_start_y = 0;
	params->draw_end_y = params->sprite_height / 2 \
		+ vars->mlx->window_height / 2;
	if (params->draw_end_y >= vars->mlx->window_height)
		params->draw_end_y = vars->mlx->window_height - 1;
	params->draw_start_x = -params->sprite_width / 2 + params->sprite_screen_x;
	if (params->draw_start_x < 0)
		params->draw_start_x = 0;
	params->draw_end_x = params->sprite_width / 2 + params->sprite_screen_x;
	if (params->draw_end_x >= vars->mlx->window_width)
		params->draw_end_x = vars->mlx->window_width - 1;
}

void	calculate_transform(t_draw_sprite_params *draw_params, \
			t_sprite_calc_params *calc_params)
{
	t_player_params	player_params;
	double			inv_det;
	int				sprite_x;
	int				sprite_y;

	player_params.dir_y = draw_params->vars->player->dir_y;
	player_params.dir_x = draw_params->vars->player->dir_x;
	player_params.plane_y = draw_params->vars->player->plane_y;
	player_params.plane_x = draw_params->vars->player->plane_x;
	sprite_x = draw_params->object_x - draw_params->vars->player->center_x;
	sprite_y = draw_params->object_y - draw_params->vars->player->center_y;
	inv_det = 1.0 / (player_params.plane_x * player_params.dir_y \
		- player_params.dir_x * player_params.plane_y);
	calc_params->transform_x = inv_det * (player_params.dir_y \
		* sprite_x - player_params.dir_x * sprite_y);
	calc_params->transform_y = inv_det * (-player_params.plane_y \
		* sprite_x + player_params.plane_x * sprite_y);
	calc_params->scale = draw_params->scale;
}

void	draw_dynamic_sprite(t_vars *vars, t_img *sprite, int object_x, \
			int object_y, int scale, int current_frame)
{
	t_sprite_params			params;
	t_sprite_calc_params	calc_params;
	t_draw_sprite_params	draw_params;

	draw_params.vars = vars;
	draw_params.sprite = sprite;
	draw_params.object_x = object_x;
	draw_params.object_y = object_y;
	draw_params.scale = scale;
	calculate_transform(&draw_params, &calc_params);
	calculate_sprite_params(vars, &calc_params, &params);
	draw_sprite_stripe(vars, &params, &calc_params, \
		sprite->frames[current_frame]);
}
