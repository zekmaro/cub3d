/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/09/10 00:35:23 by iberegsz         ###   ########.fr       */
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

void	draw_and_update_entities(t_vars *vars, t_enemy *entity_list, \
			int list_size)
{
	int	i;
	int	center_x;
	int	center_y;
	int	fire_ball_x;
	int	fire_ball_y;

	i = -1;
	while (++i < list_size)
	{
		if (!entity_list[i].is_dead)
		{
			center_x = entity_list[i].center_x;
			center_y = entity_list[i].center_y;
			draw_dynamic_sprite(vars, entity_list[i].current_animation, \
				center_x, center_y, 50);
			if (!entity_list[i].is_dead)
				search_for_player_enemy(vars, &entity_list[i]);
			if (entity_list[i].detected_player)
			{
				fire_ball_x = entity_list[i].fire_ball_x;
				fire_ball_y = entity_list[i].fire_ball_y;
				draw_dynamic_sprite(vars, entity_list[i].fire_ball, \
					fire_ball_x, fire_ball_y, 20);
			}
		}
	}
}

void	draw_map(t_vars *vars)
{
	raycast(vars);
	draw_and_update_entities(vars, vars->imp_list, vars->map->imp_list_size);
	draw_and_update_entities(vars, vars->caco_list, vars->map->caco_list_size);
	draw_gun(vars, 4.0);
	update_player_position(vars);
}
