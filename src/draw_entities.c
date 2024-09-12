/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/09/13 00:31:03 by iberegsz         ###   ########.fr       */
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
			vars->line->x0 = 100 + j * 16 - vars->map->player_x * 16;
			vars->line->y0 = 100 + i * 16 - vars->map->player_y * 16;
			vars->line->y0 += vars->minimap_update_y / 4;
			vars->line->x0 += vars->minimap_update_x / 4;
			if (vars->map->grid[i][j] == '1')
				draw_square(vars, vars->line->x0, vars->line->y0, PURPLE);
			else if (vars->map->grid[i][j] == 'D')
				draw_square(vars, vars->line->x0, vars->line->y0, GRAY);
			else
				draw_square(vars, vars->line->x0, vars->line->y0, WHITE);
		}
	}
}

void	draw_and_update_entity(t_vars *vars, t_enemy *entity)
{
	if (!entity->is_dead)
	{
		draw_dynamic_sprite(vars, entity->current_animation, \
			entity->center_x, entity->center_y, 50);
		if (!entity->is_dead)
			search_for_player_enemy(vars, entity);
		if (entity->detected_player)
			draw_dynamic_sprite(vars, entity->fire_ball, \
				entity->fire_ball_x, entity->fire_ball_y, 20);
	}
}

void	draw_and_update_entities(t_vars *vars, t_enemy *entity_list, \
			int list_size)
{
	int	i;

	i = -1;
	while (++i < list_size)
		draw_and_update_entity(vars, &entity_list[i]);
}

void	draw_map(t_vars *vars)
{
	raycast(vars);
	draw_and_update_entities(vars, vars->imp_list, vars->map->imp_list_size);
	draw_and_update_entities(vars, vars->caco_list, vars->map->caco_list_size);
	draw_gun(vars, 4.0);
	update_player_position(vars);
}
