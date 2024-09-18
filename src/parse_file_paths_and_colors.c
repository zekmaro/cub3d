/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_paths_and_colors.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:40:55 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/18 23:33:56 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			free(str);
			str = NULL;
			get_next_line(-1, &gnl_flag);
			exit_with_error(vars, "Error\nGnl failed\n");
		}
		*line = ft_strtrim(str, "\n");
		free(str);
		if (!*line)
		{
			get_next_line(-1, &gnl_flag);
			exit_with_error(vars, "Error\nFailed to allocate memory\n");
		}
	}
}

void	handle_parsing_loop(t_vars *vars, t_parse_context *ctx)
{
	char	*str;
	int		gnl_flag;

	gnl_flag = 0;
	while (*(ctx->line) != NULL && *(ctx->parsed_components) < 6)
	{
		(*(ctx->count_lines))++;
		if (ft_strncmp(*(ctx->line), "1", 1) == 0 \
			|| ft_strncmp(*(ctx->line), "0", 1) == 0)
		{
			*(ctx->line_left) = ft_strdup(*(ctx->line));
			free(*(ctx->line));
			*(ctx->line) = NULL;
			if (!*(ctx->line_left))
				exit_with_error(vars, "Error\nFailed to allocate memory\n");
			break ;
		}
		if (ft_strlen(*(ctx->line)) > 0)
		{
			parse_line(ctx->vars, *(ctx->line));
			(*(ctx->parsed_components))++;
		}
		free(*(ctx->line));
		str = get_next_line(ctx->fd, &gnl_flag);
		if (gnl_flag == 1)
		{
			free(str);
			str = NULL;
			get_next_line(-1, &gnl_flag);
			exit_with_error(vars, "Error\nGnl failed\n");
		}
		*(ctx->line) = ft_strtrim(str, "\n");
		free(str);
		if (!*(ctx->line))
			exit_with_error(vars, "Error\nFailed to allocate memory\n");
	}
}

void	handle_empty_lines(t_vars *vars, char **line, \
			int *count_lines, int fd)
{
	char	*str;
	int		gnl_flag;

	gnl_flag = 0;
	while (*line != NULL && ft_strlen(*line) == 0)
	{
		free(*line);
		str = get_next_line(fd, &gnl_flag);
		if (gnl_flag == 1)
		{
			free(str);
			str = NULL;
			get_next_line(-1, &gnl_flag);
			exit_with_error(vars, "Error\nGnl failed\n");
		}
		(*count_lines)++;
		*line = ft_strtrim(str, "\n");
		free(str);
		if (!*line)
			exit_with_error(vars, "Error\nFailed to allocate memory\n");
	}
}

void	check_parsing_errors(t_vars *vars, int parsed_components, char *line)
{
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
}

int	parse_file_paths_and_colors(int fd, t_vars *vars, char **line_left)
{
	char			*line;
	int				parsed_components;
	int				count_lines;
	t_parse_context	ctx;

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
	check_parsing_errors(vars, parsed_components, line);
	*line_left = ft_strdup(line);
	free(line);
	return (count_lines);
}
