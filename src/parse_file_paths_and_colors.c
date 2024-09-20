/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_paths_and_colors.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:40:55 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/20 13:37:18 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_empty_lines(t_vars *vars, char **line, int *count_lines, int fd)
{
	char	*str;
	int		gnl_flag;

	gnl_flag = 0;
	while (*line != NULL && ft_strlen(*line) == 0)
	{
		free(*line);
		str = get_next_line(fd, &gnl_flag);
		if (gnl_flag == 1)
			handle_gnl_error(vars, &str, &gnl_flag);
		(*count_lines)++;
		*line = ft_strtrim(str, "\n");
		free(str);
		if (!*line)
			handle_gnl_memory_error(vars, &gnl_flag);
	}
}

int	check_parsing_errors(t_vars *vars, int parsed_components, char *line)
{
	if (line == NULL)
		return (0);
	else if (parsed_components < 6)
		return (0);
	else if (!vars->texture_names[0] || !vars->texture_names[1] \
		|| !vars->texture_names[2] || !vars->texture_names[3])
		return (0);
	else if (vars->floor_color == -1 || vars->ceiling_color == -1)
		return (0);
	return (1);
}

static void	handle_line_left(t_vars *vars, char **line_left, char *line, int fd)
{
	*line_left = ft_strdup(line);
	if (!*line_left)
	{
		free(line);
		get_next_line(-1, NULL);
		ft_close(vars, fd);
		free_and_exit(vars);
	}
}

static void	handle_parsing_error(t_vars *vars, char *line, int fd)
{
	int	gnl_flag;

	gnl_flag = 0;
	handle_gnl_error_close(vars, fd, &line, &gnl_flag);
	exit_with_error(vars, "Error\nFailed to read map file\n");
}

int	parse_file_paths_and_colors(int fd, t_vars *vars, char **line_left)
{
	t_parse_context	ctx;
	int				parsed_components;
	int				count_lines;
	char			*line;

	count_lines = 0;
	parsed_components = 0;
	handle_initial_line(vars, &line, line_left, fd);
	ctx.line = &line;
	ctx.parsed_components = &parsed_components;
	ctx.count_lines = &count_lines;
	ctx.vars = vars;
	ctx.line_left = line_left;
	ctx.fd = fd;
	handle_parsing_loop(vars, &ctx);
	handle_empty_lines(vars, &line, &count_lines, fd);
	if (!check_parsing_errors(vars, parsed_components, line))
		handle_parsing_error(vars, line, fd);
	handle_line_left(vars, line_left, line, fd);
	free(line);
	return (count_lines);
}
