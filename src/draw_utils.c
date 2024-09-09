/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:38:26 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/09 23:59:37 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_vars *vars, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < vars->unit_size)
	{
		j = -1;
		while (++j < vars->unit_size)
			put_pixel_to_image(vars, x + j, y + i, color);
	}
}

void	rotate_around_point(t_vars *vars, int *x, int *y)
{
	int		temp_x;
	int		temp_y;
	double	angle;
	int		cx;
	int		cy;

	angle = vars->player->angle;
	cx = vars->player->center_x;
	cy = vars->player->center_y;
	temp_x = *x - cx;
	temp_y = *y - cy;
	*x = temp_x * cos(angle) - temp_y * sin(angle) + cx;
	*y = temp_x * sin(angle) + temp_y * cos(angle) + cy;
}
