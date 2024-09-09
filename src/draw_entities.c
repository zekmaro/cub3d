/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/09/09 13:03:26 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	double plane_length;

	vars->player->center_x = vars->player->x + vars->player->player_size / 2;
	vars->player->center_y = vars->player->y + vars->player->player_size / 2;
	vars->player->dir_x = cos(vars->player->angle);
	vars->player->dir_y = sin(vars->player->angle);
	plane_length = tan(vars->player->fov / 2);
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

void	draw_monster(t_vars *vars, unsigned int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	i = 0;
	//update_player_position(vars);
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			pixel_x = vars->imp->center_x - 4 + j;
			pixel_y = vars->imp->center_y - 4 + i;
			//rotate_around_point(vars, &pixel_x, &pixel_y);
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

void	draw_ray_segment_player(t_vars *vars)
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

void	cast_ray_enemy(t_vars *vars, t_enemy *enemy, double angle_offset)
{
	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_angle;

	ray_angle = enemy->angle + angle_offset;
	ray_x = enemy->center_x;
	ray_y = enemy->center_y;
	ray_dir_x = ray_x;
	ray_dir_y = ray_y;
	while (!is_wall(vars, ray_dir_y, ray_dir_x))
	{
		ray_dir_x += cos(ray_angle);
		ray_dir_y += sin(ray_angle);
		//put_pixel_to_image(vars, (int)ray_dir_x, (int)ray_dir_y, BLUE);
		if (!enemy->detected_player)
		{
			enemy->detected_player = is_player(vars, ray_dir_y, ray_dir_x);
			if (enemy->detected_player && angle_offset > 0.00)
				enemy->rot_dir = 1;
			else if (enemy->detected_player && angle_offset < 0.00)
				enemy->rot_dir = -1;
		}
	}
}

void	search_for_player_enemy(t_vars *vars, t_enemy *enemy)
{
	double	fov_half;
	double	radian;

	fov_half = vars->player->fov / 2;
	radian = 0;
	enemy->detected_player = 0;
	while (radian < vars->player->fov)
	{
		cast_ray_enemy(vars, enemy, -fov_half + radian);
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
			else if (vars->map->grid[i][j] == 'D')
				draw_square(vars, vars->line->x0, vars->line->y0, YELLOW);
			else
				draw_square(vars, vars->line->x0, vars->line->y0, WHITE);
			j++;
		}
		i++;
	}
}

void	draw_door(t_vars *vars)
{
	double dirY = vars->player->dir_y;
	double dirX = vars->player->dir_x;
	double planeY = vars->player->plane_y;
	double planeX = vars->player->plane_x;
	int spriteX = vars->door->center_x - vars->player->center_x;
	int spriteY = vars->door->center_y + 32 - vars->player->center_y;
	t_img *tmp = vars->door->textures->frames[2];

	double invDet = 1.0 / (planeX * dirY - dirX * planeY);
	
	double transformX = invDet * (dirY * spriteX - dirX * spriteY);
	double transformY = invDet * (-planeY * spriteX + planeX * spriteY);
	
	int spriteScreenX = (int)((vars->mlx->window_width / 2) * (1 + transformX / transformY));
	int spriteHeight = abs((int)(vars->mlx->window_height * 64 / transformY));
	int spriteWidth = abs((int)(vars->mlx->window_height * 128 / transformY));

	int drawStartY = -spriteHeight / 2 + vars->mlx->window_height / 2;
	if (drawStartY < 0) drawStartY = 0;

	int drawEndY = spriteHeight / 2 + vars->mlx->window_height / 2;
	if (drawEndY >= vars->mlx->window_height) drawEndY = vars->mlx->window_height - 1;

	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	if (drawStartX < 0) drawStartX = 0;

	int drawEndX = spriteWidth / 2 + spriteScreenX;
	if (drawEndX >= vars->mlx->window_width) drawEndX = vars->mlx->window_width - 1;

	//printf("transformY %f transformX %f drawEndY %d drawEndX %d drawStartY %d drawStartX %d \n", transformY, transformX, drawEndY, drawEndX, drawStartY, drawStartX);
	for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
	// Calculate the X-coordinate in the sprite's texture
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * tmp->width / spriteWidth) / 256;

		if (transformY > 0 && stripe > 0 && stripe < vars->mlx->window_width && transformY < vars->zbuffer[stripe]) {
			for (int y = drawStartY; y < drawEndY; y++) {
				// Calculate the Y-coordinate in the sprite's texture
				int d = (y - vars->mlx->window_height / 2 + spriteHeight / 2) * 256;
				int texY = ((d * tmp->height) / spriteHeight) / 256;

				// Get the pixel color from the sprite's texture
				int color = get_texture_color(tmp, texX, texY);
				if (color != -1) {
					put_pixel_to_image(vars, stripe, y, color);

					vars->zbuffer[stripe] = transformY;
				}
			}
		}
    }
}

void	draw_fire(t_vars *vars, double scale)
{

	int		screen_x, screen_y;
	int		tex_x, tex_y;
	int color;
	t_img *temp = (t_img *)vars->player->fire->frames[vars->player->fire->current_frame];
	int		gun_width = temp->width;   // Original texture width
	int		gun_height = temp->height;  // Original texture height
	int		scaled_width = gun_width * scale;
	int		scaled_height = gun_height * scale;
	int		screen_x_start = (vars->mlx->window_width / 2) - (scaled_width / 2) + 18;
	int		screen_y_start = vars->mlx->window_height - scaled_height;
	for (screen_y = 0; screen_y < scaled_height; screen_y++)
	{
		tex_y = screen_y / scale;
		for (screen_x = 0; screen_x < scaled_width; screen_x++)
		{
			tex_x = screen_x / scale;
			color = get_texture_color(temp, tex_x, tex_y);
			if (color != -1)
			{
				put_pixel_to_image(vars, screen_x_start + screen_x, screen_y_start + screen_y - 250, color);
			}
		}
	}
}

void	draw_gun(t_vars *vars, double scale)
{
	int		screen_x, screen_y;
	int		tex_x, tex_y;
	int color;
	t_img *temp = (t_img *)vars->player->gun->frames[vars->player->gun->current_frame];
	int		gun_width = temp->width;   // Original texture width
	int		gun_height = temp->height;  // Original texture height
	int		scaled_width = gun_width * scale;
	int		scaled_height = gun_height * scale;
	int		screen_x_start = (vars->mlx->window_width / 2) - (scaled_width / 2);
	int		screen_y_start = vars->mlx->window_height - scaled_height;
	for (screen_y = 0; screen_y < scaled_height; screen_y++)
	{
		tex_y = screen_y / scale;
		for (screen_x = 0; screen_x < scaled_width; screen_x++)
		{
			tex_x = screen_x / scale;
			color = get_texture_color(temp, tex_x, tex_y);
			if (color != -1)
			{
				put_pixel_to_image(vars, screen_x_start + screen_x, screen_y_start + screen_y - 100, color);
			}
		}
	}
}

void	draw_dynamic_sprite(t_vars *vars, t_img *sprite, int object_x, int object_y, int scale)
{
	double dirY = vars->player->dir_y;
	double dirX = vars->player->dir_x;
	double planeY = vars->player->plane_y;
	double planeX = vars->player->plane_x;
	int spriteX = object_x - vars->player->center_x;
	int spriteY = object_y - vars->player->center_y;
	t_img *tmp = sprite->frames[sprite->current_frame];

	double invDet = 1.0 / (planeX * dirY - dirX * planeY);
	
	double transformX = invDet * (dirY * spriteX - dirX * spriteY);
	double transformY = invDet * (-planeY * spriteX + planeX * spriteY);
	
	int spriteScreenX = (int)((vars->mlx->window_width / 2) * (1 + transformX / transformY));
	int spriteHeight = abs((int)(vars->mlx->window_height * scale / transformY));
	int spriteWidth = abs((int)(vars->mlx->window_height * scale / transformY));

	int drawStartY = -spriteHeight / 2 + vars->mlx->window_height / 2;
	if (drawStartY < 0) drawStartY = 0;

	int drawEndY = spriteHeight / 2 + vars->mlx->window_height / 2;
	if (drawEndY >= vars->mlx->window_height) drawEndY = vars->mlx->window_height - 1;

	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	if (drawStartX < 0) drawStartX = 0;

	int drawEndX = spriteWidth / 2 + spriteScreenX;
	if (drawEndX >= vars->mlx->window_width) drawEndX = vars->mlx->window_width - 1;

	//printf("transformY %f transformX %f drawEndY %d drawEndX %d drawStartY %d drawStartX %d \n", transformY, transformX, drawEndY, drawEndX, drawStartY, drawStartX);
	for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
	// Calculate the X-coordinate in the sprite's texture
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * tmp->width / spriteWidth) / 256;
		if (transformY > 0 && stripe > 0 && stripe < vars->mlx->window_width && transformY < vars->zbuffer[stripe]) {
			for (int y = drawStartY; y < drawEndY; y++) {
				// Calculate the Y-coordinate in the sprite's texture
				int d = (y - vars->mlx->window_height / 2 + spriteHeight / 2) * 256;
				int texY = ((d * tmp->height) / spriteHeight) / 256;

				// Get the pixel color from the sprite's texture
				int color = get_texture_color(tmp, texX, texY);
				if (color != -1) {
					put_pixel_to_image(vars, stripe, y + 50, color);

					vars->zbuffer[stripe] = transformY;
				}
			}
		}
    }
}

// void	draw_satatic_sprite()
// {

// }

void	draw_map(t_vars *vars)
{
	raycast(vars);
	int i = 0;
	while (i < vars->map->imp_list_size)
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
					vars->imp_list[i].fire_ball_x, vars->imp_list[i].fire_ball_y, 20);
			}
		}
		i++;
	}
	i = 0;
	while (i < vars->map->caco_list_size)
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
					vars->caco_list[i].fire_ball_x, vars->caco_list[i].fire_ball_y, 20);
			}
		}
		i++;
	}
	draw_gun(vars, 4.0);
	update_player_position(vars);
}
