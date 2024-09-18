/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:19:49 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/17 02:09:20 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_new_lines(int fd, char *line_left)
{
	char	*line;
	int		new_lines;

	new_lines = 0;
	//line = get_next_line(fd);
	//(void)line_left;
	line = line_left;
	printf("Line in count lines '%s'\n", line);
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

int check_first_row(char *line)
{
	int i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1')
		{
			printf("NOPE\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int check_last_row(char *line)
{
	int i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' || line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	validate_line(char *line, int row, t_map *map)
{
	int	i;

	i = 0;
	printf("%s ", line);
	while ((line[i] == ' ' || line[i] == '\t'
		|| line[i] == '\r' || line[i] == '\f' || line[i] == '\v'))
		i++;
	if (line[i] != '1')
		return (0);
	if (row == 0)
		return (check_first_row(line + i));
	if (row == map->height)
		return (check_last_row(line));
	while (line[i] && line[i] != '\n')
	{
		if (row == 1)
		{
			if (map->grid[0][i] != '1')
				return (0);
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
		if (i > 0 && line[i] == '0'
			&& (map->grid[row - 1][i] == ' '
			|| line[i + 1] == ' '
			|| line[i - 1] == ' '))
		{
			return (0);
		}
		if (i > 0 && line[i] == ' '
			&& map->grid[row - 1][i] == '0')
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
			printf("Line[%d] %s\n", i, line);
			return (perror("Error\nInvalid character in map\n"), 0);
		}
		i++;
	}
	if (i > map->width)
		map->width = i;
	return (1);
}

int	read_map(int fd, t_map *map, char *file_name, char **line_left, int readed_lines)
{
    char	*line;
    int		i;

    i = 0;
    map->height = count_new_lines(fd, *line_left);
    //printf("Read map: map height: %d line left: %s\n", map->height, *line_left);
    printf("Read map: map height: %d\n", map->height);
	fd = open(file_name, O_RDONLY);
    if (fd < 0 || map->height <= 0)
        return (close(fd), 0);
    map->grid = ft_calloc(map->height + 1, sizeof(char *));
    if (!map->grid)
        return (close(fd), 0);
    while (readed_lines-- > 0)
	{
		printf("Readed lines: %d\n", readed_lines);
		line = get_next_line(fd);
		printf("Line: %s\n", line);
		if (readed_lines == 0)
			break;
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
		//printf("Line in if in read line after skipping: %s\n", line);
		line = get_next_line(fd);
    }
    close(fd);
    return (1);
}
