/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:20:34 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 21:52:33 by iberegsz         ###   ########.fr       */
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

void	handle_pixel(t_vars *vars, t_pix_inf *pix_inf)
{
	if (is_monster(vars, pix_inf->map_x, pix_inf->map_y))
		handle_monster(vars, pix_inf->ray_id, pix_inf->y, pix_inf->color);
	else
		handle_wall(vars, pix_inf->ray_id, pix_inf->y, pix_inf->color);
}
// else if (is_door(vars, pix_inf->map_x, pix_inf->map_y))
// 	handle_door(vars, pix_inf->ray_id, pix_inf->y, pix_inf->color);

int	get_texture_color_at_y(t_vars *vars, t_tex_typ texture_index, \
	int y, t_tex_coords *coords)
{
	get_texture_coords(vars, texture_index, &coords->tex_x);
	coords->tex_y = (int)((y - vars->ray->draw_start) * vars->unit_size \
		/ vars->ray->line_height);
	return (get_texture_color(vars->textures[texture_index], coords->tex_x, \
		coords->tex_y));
}
