/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:11:26 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/22 00:24:13 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
