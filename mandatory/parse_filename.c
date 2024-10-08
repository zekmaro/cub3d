/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:11:26 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/28 13:58:24 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	handle_stuff(t_vars *vars,
				t_read_map_context *ctx)
{
	free(*ctx->line_left);
	get_next_line(-1, NULL);
	ft_close(vars, ctx->fd);
}

int	is_hidden_file(char *file_name, t_vars *vars,
				t_read_map_context *ctx)
{
	const char	*last_separator;

	if (!file_name)
		return (handle_stuff(vars, ctx), 0);
	last_separator = ft_strrchr(file_name, '/');
	if (!last_separator)
		last_separator = file_name;
	else
		last_separator++;
	if (last_separator[0] == '.')
		return (handle_stuff(vars, ctx), 0);
	return (1);
}
