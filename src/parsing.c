/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:59:53 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/19 15:08:33 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_new_lines(t_vars *vars, int fd, char *line_left)
{
	char	*line;
	int		new_lines;
	int		gnl_flag;

	gnl_flag = 0;
	new_lines = 0;
	line = line_left;
	while (line != NULL)
	{
		new_lines++;
		free(line);
		line = get_next_line(fd, &gnl_flag);
		if (gnl_flag == 1)
		{
			free(line);
			line = NULL;
			ft_close(vars, fd);
			get_next_line(-1, &gnl_flag);
			return (0);
		}
	}
	ft_close(vars, fd);
	return (new_lines);
}

int	handle_player_direction(char *line, int i, int row, t_map *map)
{
	if (map->player_dir != 0)
		return (ft_putstr_fd("Error\nMultiple player directions found\n", 2), \
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
