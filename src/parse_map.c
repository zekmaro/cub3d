/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 01:55:09 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/18 16:54:47 by iberegsz         ###   ########.fr       */
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

int	parse_file_paths_and_colors(int fd, t_vars *vars, char **line_left)
{
	char	*line;
	int		parsed_components;
	int		count_lines;

	count_lines = 0;
	parsed_components = 0;
	if (*line_left != NULL)
	{
		line = ft_strdup(*line_left);
		free(*line_left);
		*line_left = NULL;
	}
	else
	{
		line = ft_strtrim(get_next_line(fd), "\n");
	}
	while (line != NULL && parsed_components < 6)
	{
		count_lines++;
		if (ft_strncmp(line, "1", 1) == 0 || ft_strncmp(line, "0", 1) == 0)
		{
			*line_left = ft_strdup(line);
			free(line);
			break ;
		}
		if (ft_strlen(line) > 0)
		{
			parse_line(vars, line);
			parsed_components++;
		}
		free(line);
		line = ft_strtrim(get_next_line(fd), "\n");
	}
	while (line != NULL && ft_strlen(line) == 0)
	{
		count_lines++;
		free(line);
		line = ft_strtrim(get_next_line(fd), "\n");
	}
	if (line == NULL)
		exit_with_error(vars, "Error\nFailed to read map file\n");
	if (parsed_components < 6)
		exit_with_error(vars, \
		"Error\nIncomplete map file: missing textures or colors\n");
	if (!vars->texture_names[0] || !vars->texture_names[1] \
		|| !vars->texture_names[2] || !vars->texture_names[3])
		exit_with_error(vars, "Error\nMissing one or more texture paths\n");
	if (vars->floor_color == -1 || vars->ceiling_color == -1)
		exit_with_error(vars, "Error\nMissing floor or ceiling color\n");
	*line_left = ft_strdup(line);
	free(line);
	return (count_lines);
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
		return (perror("\Error\nMap is not surrounded by '1's\n"), \
			exit(EXIT_FAILURE), 0);
	fill_with_ones(map);
	return (1);
}

// int	read_map_form_file(int fd, t_map *map, t_vars *vars, char *file_name)
// {
// 	map->height = count_new_lines(fd);
// 	close(fd);
// 	fd = open(file_name, O_RDONLY);
// 	if (fd < 0 || map->height <= 0)
// 		return (0);
// 	map->grid = ft_calloc(map->height + 1, sizeof(char *));
// 	if (!map->grid)
// 		return (close(fd), 0);
// 	(void)vars;
// 	//parse_file_paths_and_colors(fd, vars);
// 	parse_map(fd, map);
// 	close(fd);
// 	return (1);
// }
