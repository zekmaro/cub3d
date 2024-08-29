/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:59:58 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/29 18:44:56 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	define_step(const int a, const int b)
{
	if (a < b)
		return (1);
	else if (a > b)
		return (-1);
	else
		return (0);
}

void	get_line_data(t_line *line)
{
	line->step_x = define_step(line->x0, line->x1);
	line->step_y = define_step(line->y0, line->y1);
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0);
	line->amount_pixels = sqrt(line->dx * line->dx + line->dy * line->dy);
}

void	increment_step(int *x0, int *y0, t_line *line)
{
	int	error;

	error = abs(*x0 - line->x0) * line->dy - abs(*y0 - line->y0) * line->dx;
	if (line->step_x && !error)
	{
		*x0 += line->step_x;
	}
	else if (line->step_y && !error)
	{
		*y0 += line->step_y;
	}
	else if (error < 0)
	{
		*x0 += line->step_x;
	}
	else if (error > 0)
	{
		*y0 += line->step_y;
	}
}

void	draw_line(t_vars *vars, unsigned long color)
{
	int	x0;
	int	y0;
	int	i;

	get_line_data(vars->line);
	i = 0;
	x0 = vars->line->x0;
	y0 = vars->line->y0;
	while (1)
	{
		put_pixel_to_image(vars, x0, y0, color);
		if (x0 == vars->line->x1 && y0 == vars->line->y1)
			break ;
		increment_step(&x0, &y0, vars->line);
		i++;
	}
}