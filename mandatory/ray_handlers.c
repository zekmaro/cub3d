/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:20:34 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/18 20:40:22 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_monster(t_vars *vars, int ray_id, int y, int color)
{
	put_pixel_to_image(vars, ray_id, y, color);
}

void	handle_door(t_vars *vars, int ray_id, int y, int color)
{
	put_pixel_to_image(vars, ray_id, y, color);
}

void	handle_wall(t_vars *vars, int ray_id, int y, int color)
{
	put_pixel_to_image(vars, ray_id, y, color);
}

int	get_texture_color_at_y(t_vars *vars, t_tex_typ texture_index, \
	int y, t_tex_coords *coords)
{
	get_texture_coords(vars, texture_index, &coords->tex_x);
	coords->tex_y = (int)((y - vars->ray->draw_start) * vars->unit_size \
		/ vars->ray->line_height);
	return (get_texture_color(vars->textures[texture_index], coords->tex_x, \
		coords->tex_y));
}
