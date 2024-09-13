/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:40:10 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/14 00:36:26 by iberegsz         ###   ########.fr       */
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

	if (!texture || !texture->addr)
	{
		perror("Error: Null texture or texture address\n");
		return (-1);
	}
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
	{
		perror("Error: Texture coordinates out of bounds\n");
		return (-1);
	}
	index = (x * (texture->bits_per_pixel / 8)) + (y * texture->line_len);
	color = (texture->addr[index] & 0xFF) \
		| ((texture->addr[index + 1] & 0xFF) << 8) \
		| ((texture->addr[index + 2] & 0xFF) << 16);
	if ((color & 0x00FFFFFF) == TRANSPARENT)
		return (-1);
	return (color);
}
