/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:42:19 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/22 00:16:18 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	handle_line_left_ctx(t_vars *vars, t_parse_context *ctx)
{
	*(ctx->line_left) = ft_strdup(*(ctx->line));
	free(*(ctx->line));
	*(ctx->line) = NULL;
	if (!*(ctx->line_left))
		exit_with_error(vars, "Error\nFailed to allocate memory\n");
}

static void	read_next_line(t_vars *vars, t_parse_context *ctx, int *gnl_flag)
{
	char	*str;
	char	*save;
	int		i;

	str = get_next_line(ctx->fd, gnl_flag);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' \
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	save = str;
	str += i;
	if (*gnl_flag == 1)
		handle_gnl_error(vars, &str, gnl_flag);
	*(ctx->line) = ft_strtrim(str, "\n");
	free(save);
	if (!*(ctx->line))
		handle_gnl_memory_error(vars, gnl_flag);
}

int	process_line(t_vars *vars, t_parse_context *ctx)
{
	if (ft_strlen(*(ctx->line)) > 0)
	{
		if (!parse_line(vars, *(ctx->line)))
			return (0);
		(*(ctx->parsed_components))++;
	}
	return (1);
}

void	cleanup_line_left(char **line_left)
{
	if (*line_left)
	{
		free(*line_left);
		*line_left = NULL;
	}
}

int	handle_parsing_loop(t_vars *vars, t_parse_context *ctx)
{
	int	gnl_flag;

	gnl_flag = 0;
	while (*(ctx->line) != NULL && *(ctx->parsed_components) < 6)
	{
		(*(ctx->count_lines))++;
		if (ft_strncmp(*(ctx->line), "1", 1) == 0 \
			|| ft_strncmp(*(ctx->line), "0", 1) == 0)
		{
			handle_line_left_ctx(vars, ctx);
			break ;
		}
		if (!process_line(vars, ctx))
			return (0);
		free(*(ctx->line));
		read_next_line(vars, ctx, &gnl_flag);
	}
	cleanup_line_left(ctx->line_left);
	return (1);
}
