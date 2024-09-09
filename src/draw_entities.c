/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/09/10 00:03:23 by iberegsz         ###   ########.fr       */
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
