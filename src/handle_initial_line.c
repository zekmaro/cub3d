/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_initial_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 01:55:09 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/19 00:30:39 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	handle_gnl_error(t_vars *vars, char *str, int *gnl_flag)
{
	free(str);
	str = NULL;
	get_next_line(-1, gnl_flag);
	exit_with_error(vars, "Error\nGnl failed\n");
}

static void	handle_memory_error(t_vars *vars, int *gnl_flag)
{
	get_next_line(-1, gnl_flag);
	exit_with_error(vars, "Error\nFailed to allocate memory\n");
}

void	handle_initial_line(t_vars *vars, char **line, \
			char **line_left, int fd)
{
	char	*str;
	int		gnl_flag;

	gnl_flag = 0;
	if (*line_left != NULL)
	{
		*line = ft_strdup(*line_left);
		free(*line_left);
		*line_left = NULL;
		if (!*line)
			exit_with_error(vars, "Error\nFailed to allocate memory\n");
	}
	else
	{
		str = get_next_line(fd, &gnl_flag);
		if (gnl_flag == 1)
		{
			handle_gnl_error(vars, str, &gnl_flag);
			exit(EXIT_FAILURE);
		}
		*line = ft_strtrim(str, "\n");
		if (!*line)
			handle_memory_error(vars, &gnl_flag);
	}
}
