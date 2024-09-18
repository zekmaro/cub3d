/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:19:49 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/18 17:00:19 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_new_lines(int fd, char *line_left)
{
	char	*line;
	int		new_lines;

	new_lines = 0;
	line = line_left;
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
		return (perror("Error\nMultiple player directions found\n"), \
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
	int	last_zero_index;

	i = 0;
	printf("%s ", line);
	while ((line[i] == ' ' || line[i] == '\t' \
		|| line[i] == '\r' || line[i] == '\f' || line[i] == '\v'))
		i++;
	if (line[i] != '1' || line[ft_strlen(line) - 2] != '1')
		return (0);
	if (row == 0)
		return (check_first_row(line + i));
	if (row == map->height)
		return (check_last_row(line));
	else if (row != 0)
	{
		last_zero_index = find_last_zero_index(map->grid[row - 1]);
		if (last_zero_index != 0)
		{
			if (ft_strlen(line) - 1 < (size_t)last_zero_index)
				return (0);
		}
	}
	while (line[i] && line[i] != '\n')
	{
		if (row == 1)
		{
			if (map->grid[0][i] != '1')
				return (0);
		}
		if (line[i] == ' ')
		{
			if (i > 0 && ((ft_strlen(map->grid[row - 1]) - 1 >= (size_t)i)))
			{
				printf("%d\n", i);
				if (map->grid[row - 1][i] == '0')
					return (0);
			}
		}
		if (row == map->height)
		{
			if (ft_strlen(line) < ft_strlen(map->grid[row - 1]))
				return (0);
			else
			{
				if (line[i] == '0')
					return (1);
			}
		}
		if (line[i] == '0' && i > 0 \
			&& ((ft_strlen(map->grid[row - 1]) - 1 < (size_t)i) \
			|| map->grid[row - 1][i] == ' ' \
			|| line[i + 1] == ' ' \
			|| line[i - 1] == ' '))
		{
			return (0);
		}
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
		{
			return (perror("Error\nInvalid character in map\n"), 0);
		}
		i++;
	}
	if (i > map->width)
		map->width = i;
	return (1);
}

int	read_map(int fd, t_map *map, char *file_name, char **line_left, \
		int readed_lines)
{
	char	*line;
	int		i;

	i = 0;
	map->height = count_new_lines(fd, *line_left);
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || map->height <= 0)
		return (close(fd), 0);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (close(fd), 0);
	while (readed_lines-- > 0)
	{
		line = get_next_line(fd);
		if (readed_lines == 0)
			break ;
		free(line);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!validate_line(line, i, map))
		{
			free(line);
			close(fd);
			return (0);
		}
		map->grid[i++] = line;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
