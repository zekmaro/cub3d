/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_gnl_errors_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:17:21 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/24 16:59:10 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_gnl_error(t_vars *vars, char **str, int *gnl_flag)
{
	free(*str);
	*str = NULL;
	get_next_line(-1, gnl_flag);
	exit_with_error(vars, "Error\nGnl failed\n");
}

void	handle_gnl_memory_error(t_vars *vars, int *gnl_flag)
{
	get_next_line(-1, gnl_flag);
	exit_with_error(vars, "Error\nFailed to allocate memory\n");
}

void	handle_gnl_error_char(t_vars *vars, int fd, char **line)
{
	free(*line);
	*line = NULL;
	ft_close(vars, fd);
	get_next_line(-1, NULL);
	exit_with_error(vars, "Error\nInvalid char\n");
}

int	handle_gnl_error_close(t_vars *vars, int fd, char **line, int *gnl_flag)
{
	free(*line);
	*line = NULL;
	get_next_line(-1, gnl_flag);
	ft_close(vars, fd);
	return (0);
}
