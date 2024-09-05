/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/09/01 02:01:00 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdint.h>

void	draw_square(t_vars *vars, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->unit_size)
	{
		j = 0;
		while (j < vars->unit_size)
		{
			put_pixel_to_image(vars, x + j, y + i, color);
			j++;
		}
		i++;
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

void	update_player_position(t_vars *vars)
{
	vars->player->center_x = vars->player->x + vars->player->player_size / 2;
	vars->player->center_y = vars->player->y + vars->player->player_size / 2;
	vars->player->dir_x = cos(vars->player->angle);
    vars->player->dir_y = sin(vars->player->angle);
    double plane_length = tan(vars->player->fov / 2);
    vars->player->plane_x = -vars->player->dir_y * plane_length;
    vars->player->plane_y = vars->player->dir_x * plane_length;
}

void	draw_player(t_vars *vars, unsigned int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	i = 0;
	update_player_position(vars);
	while (i < vars->player->player_size)
	{
		j = 0;
		while (j < vars->player->player_size)
		{
			pixel_x = vars->player->x + j;
			pixel_y = vars->player->y + i;
			rotate_around_point(vars, &pixel_x, &pixel_y);
			put_pixel_to_image(vars, pixel_x, pixel_y, color);
			j++;
		}
		i++;
	}
}

void	draw_ray(t_vars *vars, double angle_offset)
{
	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_angle;

	ray_angle = vars->player->angle + angle_offset;
	ray_x = vars->player->center_x;
	ray_y = vars->player->center_y;
	ray_dir_x = ray_x;
	ray_dir_y = ray_y;
	while (!is_wall(vars, ray_dir_y, ray_dir_x))
	{
		ray_dir_x += cos(ray_angle);
		ray_dir_y += sin(ray_angle);
		put_pixel_to_image(vars, (int)ray_dir_x, (int)ray_dir_y, GREEN);
	}
}

void	draw_ray_segment(t_vars *vars)
{
	double	fov_half;
	double	radian;

	fov_half = vars->player->fov / 2;
	radian = 0;
	while (radian < vars->player->fov)
	{
		draw_ray(vars, -fov_half + radian);
		radian += 0.01;
	}
}

void	draw_minimap(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map->height)
	{
		j = 0;
		while (j < vars->map->width)
		{
			vars->line->x0 = j * vars->unit_size;
			vars->line->y0 = i * vars->unit_size;
			if (vars->map->grid[i][j] == '1')
				draw_square(vars, vars->line->x0, vars->line->y0, BEIGE);
			else if (vars->map->grid[i][j] == 'M')
				draw_square(vars, vars->line->x0, vars->line->y0, BLUE);
			else
				draw_square(vars, vars->line->x0, vars->line->y0, WHITE);
			j++;
		}
		i++;
	}
	draw_player(vars, RED);
}

void	handle_sprites(t_vars *vars)
{
	double dirY = vars->player->dir_y;
	double dirX = vars->player->dir_x;
	double planeY = vars->player->plane_y;
	double planeX = vars->player->plane_x;
	int spriteX = vars->map->monster_x * vars->unit_size + vars->unit_size / 2 - vars->player->center_x;
	int spriteY = vars->map->monster_y * vars->unit_size + vars->unit_size / 2 - vars->player->center_y;

	printf("planeY %f * dirY %f - dirX %f * planeX %f\n", planeY, dirY, dirX, planeX);
	double invDet = 1.0 / (planeX * dirY - dirX * planeY);
	
	double transformX = invDet * (dirY * spriteX - dirX * spriteY);
	double transformY = invDet * (-planeY * spriteX + planeX * spriteY);
	
	int spriteScreenX = (int)((vars->mlx->window_width / 2) * (1 + transformX / transformY));
	int spriteHeight = abs((int)(vars->mlx->window_height * 50 / transformY));
	int spriteWidth = abs((int)(vars->mlx->window_height * 50 / transformY));

	int drawStartY = -spriteHeight / 2 + vars->mlx->window_height / 2;
	if (drawStartY < 0) drawStartY = 0;

	int drawEndY = spriteHeight / 2 + vars->mlx->window_height / 2;
	if (drawEndY >= vars->mlx->window_height) drawEndY = vars->mlx->window_height - 1;

	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	if (drawStartX < 0) drawStartX = 0;

	int drawEndX = spriteWidth / 2 + spriteScreenX;
	if (drawEndX >= vars->mlx->window_width) drawEndX = vars->mlx->window_width - 1;

	printf("transformY %f transformX %f drawEndY %d drawEndX %d drawStartY %d drawStartX %d \n", transformY, transformX, drawEndY, drawEndX, drawStartY, drawStartX);
	for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
	// Calculate the X-coordinate in the sprite's texture
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 44 / spriteWidth) / 256;

		if (transformY > 0 && stripe > 0 && stripe < vars->mlx->window_width && transformY < vars->zbuffer[stripe]) {
			for (int y = drawStartY; y < drawEndY; y++) {
				// Calculate the Y-coordinate in the sprite's texture
				int d = (y - vars->mlx->window_height / 2 + spriteHeight / 2) * 256;
				int texY = ((d * 63) / spriteHeight) / 256;

				// Get the pixel color from the sprite's texture
				int color = get_texture_color(vars->animated_sprite->frames[vars->animated_sprite->current_frame], texX, texY);
				if (color != -1) {
					put_pixel_to_image(vars, stripe, y + 50, color);

					vars->zbuffer[stripe] = transformY;
				}
			}
		}
    }
}

void	draw_map(t_vars *vars)
{
	raycast(vars);
	handle_sprites(vars);
	//draw_minimap(vars);
	//draw_ray_segment(vars);	
	update_player_position(vars);
}
