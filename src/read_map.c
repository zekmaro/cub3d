/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:10:18 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/18 21:19:01 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	initialize_map(t_read_map_context *ctx)
{
	ctx->map->height = count_new_lines(ctx->fd, *(ctx->line_left));
	ctx->fd = open(ctx->file_name, O_RDONLY);
	if (ctx->fd < 0 || ctx->map->height <= 0)
		return (close(ctx->fd), 0);
	ctx->map->grid = ft_calloc(ctx->map->height + 1, sizeof(char *));
	if (!ctx->map->grid)
		return (close(ctx->fd), 0);
	return (1);
}

static int	skip_readed_lines(t_read_map_context *ctx)
{
	char	*line;

	while (ctx->readed_lines-- > 0)
	{
		line = get_next_line(ctx->fd);
		free(line);
		if (ctx->readed_lines == 0)
			break ;
	}
	return (1);
}

static int	read_and_validate_lines(t_read_map_context *ctx)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(ctx->fd);
	while (line != NULL)
	{
		if (!validate_line(line, i, ctx->map))
		{
			free(line);
			close(ctx->fd);
			return (0);
		}
		ctx->map->grid[i++] = line;
		line = get_next_line(ctx->fd);
	}
	return (1);
}

int	read_map(t_read_map_context *ctx)
{
	if (is_hidden_file(ctx->file_name) == 0)
		return (0);
	if (!initialize_map(ctx))
		return (0);
	if (!skip_readed_lines(ctx))
		return (0);
	if (!read_and_validate_lines(ctx))
		return (0);
	close(ctx->fd);
	return (1);
}
