/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 01:55:09 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/17 01:52:08 by iberegsz         ###   ########.fr       */
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
    int		count_lines = 0;

    printf("Parsing file paths and colors...\n");
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
    printf("1.st line (len: %zu): %s\n", ft_strlen(line), line);
    while (line != NULL && parsed_components < 6)
    {
        count_lines++;
        if (ft_strncmp(line, "1", 1) == 0 || ft_strncmp(line, "0", 1) == 0)
        {
            *line_left = ft_strdup(line);
            free(line);
            break;
        }
        if (ft_strlen(line) > 0)
        {
            parse_line(vars, line);
            parsed_components++;
        }
        printf("%d. line: (len: %zu): %s\n", parsed_components, ft_strlen(line), line);
        free(line);
        line = ft_strtrim(get_next_line(fd), "\n");
    }
    printf("After while count lines %d parsed components and the line is: %d \"%s\"\n", count_lines, parsed_components, line);
    while (line != NULL && ft_strlen(line) == 0)
    {
        count_lines++;
        printf("Empty line on count_lines: %d\n", count_lines);
        free(line);
        line = ft_strtrim(get_next_line(fd), "\n");
    }
    printf("Parsed components: %d\n", parsed_components);
    if (line == NULL)
        exit_with_error(vars, "Failed to read map file");
    if (parsed_components < 6)
        exit_with_error(vars, "Incomplete map file: missing textures or colors");
    if (!vars->texture_names[0] || !vars->texture_names[1] || !vars->texture_names[2] || !vars->texture_names[3])
        exit_with_error(vars, "Missing one or more texture paths");
    if (vars->floor_color == -1 || vars->ceiling_color == -1)
        exit_with_error(vars, "Missing floor or ceiling color");
    printf("Parsed all file paths and colors and in the line now '%s'\n", line);
    *line_left = ft_strdup(line);
    printf("Line left in parse: %s\n", *line_left);
    free(line);
	return(count_lines);
}

int	parse_map(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	printf("line: %s\n", line);
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
