/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_initial_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 01:55:09 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/22 00:13:46 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}

int	count_commas(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static void	handle_line_from_fd(t_vars *vars, char **line, int fd)
{
	char	*str;
	int		i;
	char	*save;
	int		gnl_flag;

	gnl_flag = 0;
	str = get_next_line(fd, &gnl_flag);
	if (gnl_flag == 1)
		handle_gnl_error(vars, &str, &gnl_flag);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' \
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	save = str;
	str += i;
	*line = ft_strtrim(str, "\n");
	free(save);
	if (!*line)
	{
		printf("HELLO ISTVAN!!!\n");
		handle_gnl_memory_error(vars, &gnl_flag);
	}
}

void	handle_initial_line(t_vars *vars, char **line, char **line_left, int fd)
{
	if (*line_left != NULL)
	{
		*line = ft_strdup(*line_left);
		free(*line_left);
		*line_left = NULL;
		if (!*line)
			exit_with_error(vars, "Error\nFailed to allocate memory\n");
	}
	else
		handle_line_from_fd(vars, line, fd);
}
