/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/09/09 22:38:57 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_minimap(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	while (++i < vars->map->height)
	{
		j = -1;
		while (++j < vars->map->width)
		{
			vars->line->x0 = j * vars->unit_size;
			vars->line->y0 = i * vars->unit_size;
			if (vars->map->grid[i][j] == '1')
				draw_square(vars, vars->line->x0, vars->line->y0, BEIGE);
			else if (vars->map->grid[i][j] == 'D')
				draw_square(vars, vars->line->x0, vars->line->y0, YELLOW);
			else
				draw_square(vars, vars->line->x0, vars->line->y0, WHITE);
		}
	}
}

void	draw_dynamic_sprite(t_vars *vars, t_img *sprite, int object_x, \
			int object_y, int scale)
{
	double	dirY;
	double	dirX;
	double	planeY;
	double	planeX;
	int		spriteX;
	int		spriteY;
	t_img	*tmp;
	double	invDet;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		spriteHeight;
	int		spriteWidth;
	int		drawStartY;
	int		stripe;
	int		y;
	int		texX;
	int		drawEndY;
	int		drawStartX;
	int		drawEndX;
	int		d;
	int		texY;
	int		color;

	dirY = vars->player->dir_y;
	dirX = vars->player->dir_x;
	planeY = vars->player->plane_y;
	planeX = vars->player->plane_x;
	spriteX = object_x - vars->player->center_x;
	spriteY = object_y - vars->player->center_y;
	tmp = sprite->frames[sprite->current_frame];
	invDet = 1.0 / (planeX * dirY - dirX * planeY);
	transformX = invDet * (dirY * spriteX - dirX * spriteY);
	transformY = invDet * (-planeY * spriteX + planeX * spriteY);
	spriteScreenX = (int)((vars->mlx->window_width / 2) \
		* (1 + transformX / transformY));
	spriteHeight = abs((int)(vars->mlx->window_height * scale / transformY));
	spriteWidth = abs((int)(vars->mlx->window_height * scale / transformY));
	drawStartY = -spriteHeight / 2 + vars->mlx->window_height / 2;
	if (drawStartY < 0)
		drawStartY = 0;
	drawEndY = spriteHeight / 2 + vars->mlx->window_height / 2;
	if (drawEndY >= vars->mlx->window_height)
		drawEndY = vars->mlx->window_height - 1;
	drawStartX = -spriteWidth / 2 + spriteScreenX;
	if (drawStartX < 0)
		drawStartX = 0;
	drawEndX = spriteWidth / 2 + spriteScreenX;
	if (drawEndX >= vars->mlx->window_width)
		drawEndX = vars->mlx->window_width - 1;
	stripe = drawStartX - 1;
	while (++stripe < drawEndX)
	{
		texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) \
			* tmp->width / spriteWidth) / 256;
		if (transformY > 0 && stripe > 0 && stripe < vars->mlx->window_width \
			&& transformY < vars->zbuffer[stripe])
		{
			y = drawStartY - 1;
			while (++y < drawEndY)
			{
				d = (y - vars->mlx->window_height / 2 + spriteHeight / 2) * 256;
				texY = ((d * tmp->height) / spriteHeight) / 256;
				color = get_texture_color(tmp, texX, texY);
				if (color != -1)
				{
					put_pixel_to_image(vars, stripe, y + 50, color);
					vars->zbuffer[stripe] = transformY;
				}
			}
		}
	}
}

void	draw_map(t_vars *vars)
{
	int	i;

	raycast(vars);
	i = -1;
	while (++i < vars->map->imp_list_size)
	{
		if (!vars->imp_list[i].is_dead)
		{
			draw_dynamic_sprite(vars, vars->imp_list[i].current_animation,
				vars->imp_list[i].center_x, vars->imp_list[i].center_y, 50);
			if (!vars->imp_list[i].is_dead)
			{
				search_for_player_enemy(vars, &vars->imp_list[i]);
			}
			if (vars->imp_list[i].detected_player)
			{
				draw_dynamic_sprite(vars, vars->imp_list[i].fire_ball,
					vars->imp_list[i].fire_ball_x, \
						vars->imp_list[i].fire_ball_y, 20);
			}
		}
	}
	i = -1;
	while (++i < vars->map->caco_list_size)
	{
		if (!vars->caco_list[i].is_dead)
		{
			draw_dynamic_sprite(vars, vars->caco_list[i].current_animation,
				vars->caco_list[i].center_x, vars->caco_list[i].center_y, 50);
			if (!vars->caco_list[i].is_dead)
			{
				search_for_player_enemy(vars, &vars->caco_list[i]);
			}
			if (vars->caco_list[i].detected_player)
			{
				draw_dynamic_sprite(vars, vars->caco_list[i].fire_ball,
					vars->caco_list[i].fire_ball_x, \
						vars->caco_list[i].fire_ball_y, 20);
			}
		}
	}
	draw_gun(vars, 4.0);
	update_player_position(vars);
}
