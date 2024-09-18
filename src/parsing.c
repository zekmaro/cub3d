/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:59:53 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/18 21:10:22 by iberegsz         ###   ########.fr       */
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

void	handle_boss(int i, int row, t_map *map)
{
	map->boss_x = i;
	map->boss_y = row;
}
