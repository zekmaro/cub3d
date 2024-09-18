/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:46:44 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/18 20:08:46 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	skip_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r' \
		|| line[i] == '\f' || line[i] == '\v')
		i++;
	return (i);
}

int	check_first_last_row(char *line, int row, t_map *map)
{
	if (row == 0)
		return (check_first_row(line));
	if (row == map->height)
		return (check_last_row(line));
	return (1);
}

int	check_last_zero_index(char *line, int row, t_map *map)
{
	int	last_zero_index;

	last_zero_index = find_last_zero_index(map->grid[row - 1]);
	if (last_zero_index != 0 \
		&& ft_strlen(line) - 1 < (size_t)last_zero_index)
		return (0);
	return (1);
}

int	validate_line_content(char *line, int i, int row, t_map *map)
{
	if (row == 1 && map->grid[0][i] != '1')
		return (0);
	if (line[i] == ' ' && i > 0 && ft_strlen(map->grid[row - 1]) - 1 \
		>= (size_t)i && map->grid[row - 1][i] == '0')
		return (0);
	if (row == map->height && ft_strlen(line) < ft_strlen(map->grid[row - 1]))
		return (0);
	if (line[i] == '0' && i > 0 && (ft_strlen(map->grid[row - 1]) - 1 \
		< (size_t)i || map->grid[row - 1][i] == ' ' || line[i + 1] == ' ' \
		|| line[i - 1] == ' '))
		return (0);
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		return (handle_player_direction(line, i, row, map));
	if (line[i] == 'B')
		handle_boss(i, row, map);
	else if (line[i] == 'M')
		map->imp_list_size++;
	else if (line[i] == 'C')
		map->caco_list_size++;
	else if (line[i] == 'D')
		map->num_doors++;
	else if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
		return (perror("Error\nInvalid character in map\n"), 0);
	return (1);
}

int	validate_line(char *line, int row, t_map *map)
{
	int	i;

	i = skip_whitespace(line);
	if (line[i] != '1' || line[ft_strlen(line) - 2] != '1')
		return (0);
	if (!check_first_last_row(line + i, row, map))
		return (0);
	if (row != 0 && !check_last_zero_index(line, row, map))
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!validate_line_content(line, i, row, map))
			return (0);
		i++;
	}
	if (i > map->width)
		map->width = i;
	return (1);
}
