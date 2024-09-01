/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:19:49 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/01 18:43:29 by iberegsz         ###   ########.fr       */
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
	return (new_lines);
}

int	validate_line(char *line, int row, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S' \
			|| line[i] == 'W' || line[i] == 'E')
		{
			if (map->player_dir != 0)
				return (printf("hello\n"), 0);
			map->player_x = i;
			map->player_y = row;
			map->player_dir = line[i];
		}
		else if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
			return (printf("world\n"), 0);
		i++;
	}
	if (i > map->width)
		map->width = i;
	return (1);
}

void	initialize_doors(t_map *map)
{
	int i;
	int j;

	map->doors = malloc(sizeof(int *) * map->height);
	i = -1;
	while (++i < map->height)
	{
		map->doors[i] = malloc(sizeof(int) * map->width);
		j = -1;
		while (++j < map->width)
		{
			if (map->grid[i][j] == 'D')
				map->doors[i][j] = DOOR_CLOSED;
			else
				map->doors[i][j] = DOOR_UNDEFINED;
		}
	}
}

int	read_map(int fd, t_map *map, char *file_name)
{
	char	*line;
	int		i;

	i = 0;
	map->height = count_new_lines(fd);
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || map->height <= 0)
		return (0);
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
	initialize_doors(map);
	return (1);
}
