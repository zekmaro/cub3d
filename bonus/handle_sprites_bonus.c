/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:03:38 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/24 17:00:10 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_sprite_frame(t_img *sprite)
{
	sprite->current_frame = (sprite->current_frame + 1) % sprite->frame_count;
}

void	calculate_sprite_distances(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->num_sprites)
		vars->sprites[i].distance = sqrt(pow(vars->player->x \
		- vars->sprites[i].x, 2) + pow(vars->player->y \
		- vars->sprites[i].y, 2));
}

void	project_sprite(t_vars *vars, t_sprite *sprite)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;

	sprite_x = sprite->x - vars->player->x;
	sprite_y = sprite->y - vars->player->y;
	inv_det = 1.0 / (vars->player->plane_x * vars->player->dir_y \
		- vars->player->dir_x * vars->player->plane_y);
	transform_x = inv_det * (vars->player->dir_y * sprite_x \
		- vars->player->dir_x * sprite_y);
	transform_y = inv_det * (-vars->player->plane_y * sprite_x \
		+ vars->player->plane_x * sprite_y);
	sprite->screen_x = (int)((vars->mlx->window_width / 2) \
		* (1 + transform_x / transform_y));
	sprite->height = ft_abs((int)(vars->mlx->window_height / transform_y));
	sprite->width = ft_abs((int)(vars->mlx->window_height / transform_y));
}

void	sort_sprites(t_vars *vars)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = -1;
	while (++i < vars->num_sprites - 1)
	{
		j = i;
		while (++j < vars->num_sprites)
		{
			if (vars->sprites[i].distance < vars->sprites[j].distance)
			{
				temp = vars->sprites[i];
				vars->sprites[i] = vars->sprites[j];
				vars->sprites[j] = temp;
			}
		}
	}
}
