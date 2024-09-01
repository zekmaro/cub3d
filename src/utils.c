/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:40:10 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/01 18:56:23 by iberegsz         ###   ########.fr       */
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

int	is_wall(t_vars *vars, int y, int x)
{
	return (vars->map->grid[y / vars->unit_size][x \
		/ vars->unit_size] == '1');
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
		if (vars->map->doors[y][x] == DOOR_CLOSED)
			return (0);
		return (1);
	}
	else
		return (0);
}

int	get_texture_color(t_img *texture, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = texture->addr + (y * texture->line_len \
		+ x * (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	if ((color & 0x00FFFFFF) == MAGENTA)
		return (-1);
	return (color);
}

long	get_elapsed_time(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) * 1000
		+ (end->tv_usec - start->tv_usec) / 1000);
}

void	get_current_time(struct timeval *time)
{
	gettimeofday(time, NULL);
}
