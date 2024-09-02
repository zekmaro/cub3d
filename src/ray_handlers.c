/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:20:34 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/02 13:30:32 by iberegsz         ###   ########.fr       */
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

void	handle_pixel(t_vars *vars, int ray_id, int y, int color, \
			int map_x, int map_y)
{
	if (is_monster(vars, map_x, map_y))
		handle_monster(vars, ray_id, y, color);
	else if (is_door(vars, map_x, map_y))
		handle_door(vars, ray_id, y, color);
	else
		handle_wall(vars, ray_id, y, color);
}

int	get_texture_color_at_y(t_vars *vars, t_tex_typ texture_index, int y, \
		int *tex_x, int *tex_y)
{
	get_texture_coords(vars, texture_index, tex_x);
	*tex_y = (int)((y - vars->ray->draw_start) * vars->unit_size \
		/ vars->ray->line_height);
	return (get_texture_color(vars->textures[texture_index], *tex_x, *tex_y));
}
