/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:10:18 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/17 01:26:13 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	open_file(const char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		perror("Error\nError opening file\n");
	return (fd);
}

static int	allocate_grid(t_map *map)
{
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
	{
		perror("Error\nError allocating grid\n");
		return (0);
	}
	return (1);
}

static void	free_grid(char **grid, int size)
{
	while (size > 0)
		free(grid[--size]);
	free(grid);
}

static int	process_line(char *line, int i, t_map *map)
{
	if (!validate_line(line, i, map))
		return (free(line), 0);
	map->grid[i] = line;
	return (1);
}

// int	read_map_refactored(int fd, t_map *map, char *file_name)
// {
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	map->height = count_new_lines(fd);
// 	close(fd);
// 	fd = open_file(file_name);
// 	if (fd < 0 || map->height <= 0)
// 		return (0);
// 	if (!allocate_grid(map))
// 		return (close(fd), 0);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		if (!process_line(line, i, map))
// 			return (free_grid(map->grid, i), close(fd), 0);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	if (line != NULL)
// 		free(line);
// 	close(fd);
// 	return (1);
// }
