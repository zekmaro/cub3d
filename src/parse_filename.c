/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:11:26 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/21 14:44:11 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int	has_cub_extension(const char *filename)
// {
// 	size_t	len;

// 	len = ft_strlen(filename);
// 	if (len < 4)
// 		return (0);
// 	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
// }

// int	is_valid_file(t_vars *vars, const char *filename)
// {
// 	int	fd;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		return (0);
// 	ft_close(vars, fd);
// 	return (1);
// }

int	is_hidden_file(char *file_name)
{
	const char	*last_separator;

	if (!file_name)
		return (0);
	last_separator = ft_strrchr(file_name, '/');
	if (!last_separator)
		last_separator = file_name;
	else
		last_separator++;
	if (last_separator[0] == '.')
		return (0);
	return (1);
}
