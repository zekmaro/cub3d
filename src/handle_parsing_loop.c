/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:42:19 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/21 13:15:30 by iberegsz         ###   ########.fr       */
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

	str = get_next_line(ctx->fd, gnl_flag);
	if (*gnl_flag == 1)
		handle_gnl_error(vars, &str, gnl_flag);
	*(ctx->line) = ft_strtrim(str, "\n");
	free(str);
	if (!*(ctx->line))
		handle_gnl_memory_error(vars, gnl_flag);
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
		if (ft_strlen(*(ctx->line)) > 0)
		{
			if (!parse_line(ctx->vars, *(ctx->line)))
				return (0);
			(*(ctx->parsed_components))++;
		}
		free(*(ctx->line));
		read_next_line(vars, ctx, &gnl_flag);
	}
	if (*(ctx->line_left))
	{
		free(*(ctx->line_left));
		*(ctx->line_left) = NULL;
	}
	return (1);
}
