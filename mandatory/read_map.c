/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:10:18 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/24 19:10:12 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	initialize_map(t_vars *vars, t_read_map_context *ctx)
{
	ctx->map->height = count_new_lines(vars, ctx->fd, *(ctx->line_left));
	ctx->fd = open(ctx->file_name, O_RDONLY);
	if (ctx->fd < 0 || ctx->map->height <= 0)
		return (ft_close(vars, ctx->fd), 0);
	ctx->map->grid = ft_calloc(ctx->map->height + 1, sizeof(char *));
	if (!ctx->map->grid)
		return (ft_close(vars, ctx->fd), 0);
	return (1);
}

static int	skip_readed_lines(t_vars *vars, t_read_map_context *ctx)
{
	char	*line;
	int		gnl_flag;

	gnl_flag = 0;
	while (ctx->readed_lines-- > 0)
	{
		line = get_next_line(ctx->fd, &gnl_flag);
		free(line);
		if (gnl_flag == 1)
		{
			ft_close(vars, ctx->fd);
			get_next_line(-1, &gnl_flag);
			return (0);
		}
		if (ctx->readed_lines == 0)
			break ;
	}
	return (1);
}

static int	read_and_validate_lines(t_vars *vars, t_read_map_context *ctx)
{
	char	*line;
	int		i;
	int		gnl_flag;

	gnl_flag = 0;
	i = 0;
	line = get_next_line(ctx->fd, &gnl_flag);
	if (gnl_flag == 1)
		return (handle_gnl_error_close(vars, ctx->fd, &line, &gnl_flag));
	while (line != NULL)
	{
		if (*line == '\n')
		{
			free(line);
			exit_with_error(vars, "Error\nEmpty line inside the map\n");
			return (0);
		}
		if (!validate_line(line, i, ctx->map))
			return (handle_gnl_error_close(vars, ctx->fd, &line, &gnl_flag));
		ctx->map->grid[i++] = line;
		line = get_next_line(ctx->fd, &gnl_flag);
		if (gnl_flag == 1)
			return (handle_gnl_error_close(vars, ctx->fd, &line, &gnl_flag));
	}
	return (1);
}

static int	put_error_msg(const char *error_message)
{
	ft_putstr_fd((char *)error_message, 2);
	return (0);
}

int	read_map(t_vars *vars, t_read_map_context *ctx)
{
	if (is_hidden_file(ctx->file_name) == 0)
		return (put_error_msg("Error\nHidden files are not allowed\n"));
	if (!initialize_map(vars, ctx))
		return (put_error_msg("Error\nFailed to initialize map\n"));
	if (!skip_readed_lines(vars, ctx))
		return (put_error_msg("Error\nFailed to skip readed lines\n"));
	if (!read_and_validate_lines(vars, ctx))
		return (put_error_msg("Error\nFailed to read and validate lines\n"));
	if (!vars->map->player_found)
		return (put_error_msg("Error\nPlayer not found in map\n"));
	ft_close(vars, ctx->fd);
	return (1);
}
