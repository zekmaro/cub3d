/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:54:25 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/22 00:07:08 by andrejarama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(t_vars *vars, int x, int y, int color)
{
	int	index;

	if (x >= 0 && x < vars->mlx->window_width
		&& y >= 0 && y < vars->mlx->window_height)
	{
		index = (x * (vars->image->bits_per_pixel / 8))
			+ (y * (vars->image->line_len));
		(vars->image->addr)[index] = color & 0xFF;
		(vars->image->addr)[index + 1] = (color >> 8) & 0xFF;
		(vars->image->addr)[index + 2] = (color >> 16) & 0xFF;
	}
}

void	clean_screen(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y != vars->mlx->window_height)
	{
		x = 0;
		while (x != vars->mlx->window_width)
		{
			put_pixel_to_image(vars, x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	get_data_image(t_vars *vars, t_img *image, t_mlx *mlx)
{
	image->mlx_img = mlx_new_image(mlx->mlx, mlx->window_width,
			mlx->window_height);
	// if (!image->mlx_img)
	// 	free_and_exit(vars);
	image->addr = mlx_get_data_addr(image->mlx_img, &(image->bits_per_pixel),
			&(image->line_len), &(image->endian));
	// if (!image->addr)
	// 	free_and_exit(vars);
}
