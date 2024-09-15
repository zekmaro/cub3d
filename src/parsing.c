/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:19:49 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/15 17:38:39 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_new_lines(int fd)
{
	char	*line;
	int		new_lines;

	new_lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		new_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (new_lines);
}

int	handle_player_direction(char *line, int i, int row, t_map *map)
{
	if (map->player_dir != 0)
		return (perror("Multiple player directions found\n"), \
					exit(EXIT_FAILURE), 1);
	map->player_x = i;
	map->player_y = row;
	map->player_dir = line[i];
	line[i] = 'P';
	return (1);
}

static void	handle_boss(int i, int row, t_map *map)
{
	map->boss_x = i;
	map->boss_y = row;
}

int	validate_line(char *line, int row, t_map *map)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S' \
			|| line[i] == 'W' || line[i] == 'E')
		{
			if (!handle_player_direction(line, i, row, map))
				return (0);
		}
		else if (line[i] == 'B')
			handle_boss(i, row, map);
		else if (line[i] == 'M')
			map->imp_list_size++;
		else if (line[i] == 'C')
			map->caco_list_size++;
		else if (line[i] == 'D')
			map->num_doors++;
		else if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
			return (perror("Error\nInvalid character in map\n"), 0);
	}
	if (i > map->width)
		map->width = i;
	return (1);
}

int	read_map(int fd, t_map *map, char *file_name)
{
	char	*line;
	int		i;

	i = 0;
	map->height = count_new_lines(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || map->height <= 0)
		return (close(fd), 0);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (close(fd), 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!validate_line(line, i, map))
			return (free(line), close(fd), 0);
		map->grid[i] = line;
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (1);
}
