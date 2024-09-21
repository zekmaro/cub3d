/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:43 by anarama           #+#    #+#             */
/*   Updated: 2024/09/21 12:51:07 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_minimap(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map->height)
	{
		j = 0;
		while ((size_t)j < ft_strlen(vars->map->grid[i]))
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
			j++;
		}
		i++;
	}
}

void	draw_and_update_entity(t_vars *vars, t_enemy *entity, int scale)
{
	t_sprite_info	sprite_info;
	t_sprite_info	fireball_info;

	if (!entity->is_dead)
	{
		sprite_info.sprite = entity->current_animation;
		sprite_info.object_x = entity->center_x;
		sprite_info.object_y = entity->center_y;
		sprite_info.scale = scale;
		sprite_info.current_frame = entity->current_frame;
		if (entity->draw)
			draw_dynamic_sprite(vars, &sprite_info);
		if (!entity->is_dead)
			search_for_player_enemy(vars, entity);
		if (entity->detected_player && entity->draw)
		{
			fireball_info.sprite = entity->fire_ball;
			fireball_info.object_x = entity->fire_ball_x;
			fireball_info.object_y = entity->fire_ball_y;
			fireball_info.scale = 20;
			fireball_info.current_frame = 0;
			draw_dynamic_sprite(vars, &fireball_info);
		}
	}
}

void	draw_and_update_entities(t_vars *vars, t_enemy *entity_list, \
			int list_size)
{
	int	i;

	i = -1;
	while (++i < list_size)
		draw_and_update_entity(vars, &entity_list[i], 50);
}

void	draw_map(t_vars *vars)
{
	if (vars == NULL)
		return ;
	raycast(vars);
	draw_and_update_entities(vars, vars->imp_list, vars->map->imp_list_size);
	draw_and_update_entities(vars, vars->caco_list, vars->map->caco_list_size);
	draw_and_update_entity(vars, vars->boss, 100);
	draw_gun(vars, 4.0);
	update_player_position(vars);
}
