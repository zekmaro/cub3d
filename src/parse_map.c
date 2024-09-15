/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 01:55:09 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/15 02:22:56 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_map_surrounded_by_ones(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->width)
	{
		if (map->grid[0][i] != '1' || map->grid[map->height - 1][i] != '1')
			return (0);
		i++;
	}
	j = 0;
	while (j < map->height)
	{
		if (map->grid[j][0] != '1' || map->grid[j][map->width - 1] != '1')
			return (0);
		j++;
	}
	return (1);
}

void	fill_with_ones(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->height)
	{
		i = 0;
		while (i < map->width)
		{
			if (map->grid[j][i] == '\0' || map->grid[j][i] == ' ')
				map->grid[j][i] = '1';
			i++;
		}
		j++;
	}
}

void	parse_file_paths_and_colors(int fd, t_vars *vars)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strncmp(line, "1", 1) == 0 || ft_strncmp(line, "0", 1) == 0)
		{
			free(line);
			break ;
		}
		if (ft_strlen(line) > 0)
			parse_line(vars, line);
		free(line);
		line = get_next_line(fd);
	}
}

int	parse_map(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line == NULL)
	{
		while (*line == ' ')
			line++;
		if (!validate_line(line, i, map))
			return (free(line), close(fd), 0);
		map->grid[i] = line;
		line = get_next_line(fd);
		i++;
		line = get_next_line(fd);
	}
	if (!is_map_surrounded_by_ones(map))
		return (perror("Map is not surrounded by '1's"), exit(EXIT_FAILURE), 0);
	fill_with_ones(map);
}

int	read_map_form_file(int fd, t_map *map, t_vars *vars, char *file_name)
{
	map->height = count_new_lines(fd);
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || map->height <= 0)
		return (0);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (close(fd), 0);
	parse_file_paths_and_colors(fd, vars);
	parse_map(fd, map);
	close(fd);
	return (1);
}
