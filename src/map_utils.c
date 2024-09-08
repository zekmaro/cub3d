/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:40:10 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/08 16:14:50 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		ft_putstr_fd(map->grid[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

int	is_player(t_vars *vars, int y, int x)
{
	return (abs(y - vars->player->center_y) < 10 && abs(x - vars->player->center_x) < 10);
}

int	is_imp(t_vars *vars, int y, int x)
{
	return (abs(y - vars->imp->center_y) < 40 && abs(x - vars->imp->center_x) < 40);
}

int	is_caco(t_vars *vars, int y, int x)
{
	return (abs(y - vars->caco->center_y) < 40 && abs(x - vars->caco->center_x) < 40);
}

int	is_wall(t_vars *vars, int y, int x)
{
	return (vars->map->grid[y / vars->unit_size][x \
		/ vars->unit_size] == '1');
}

int	is_door(t_vars *vars, int y, int x)
{
	return (vars->map->grid[y / vars->unit_size][x \
		/ vars->unit_size] == 'D');
}

int	player_inside_map(t_vars *vars, int x, int y)
{
	return (x < vars->map->width \
		&& y < vars->map->height);
}

int	can_move(t_vars *vars, int y, int x)
{
	if (player_inside_map(vars, x, y))
	{
		if (vars->map->grid[y][x] == '1')
			return (0);
		return (1);
	}
	else
		return (0);
}

int	get_texture_color(t_img *texture, int x, int y)
{
	int	index;
	int	color;

	index = (x * (texture->bits_per_pixel / 8)) + (y * texture->line_len);
	color = (texture->addr[index] & 0xFF) \
			| ((texture->addr[index + 1] & 0xFF) << 8) \
			| ((texture->addr[index + 2] & 0xFF) << 16);
	if ((color & 0x00FFFFFF) == TRANSPARENT)
		return (-1);
	return (color);
}
