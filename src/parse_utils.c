/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:59:53 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/21 16:12:27 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_first_row(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_last_row(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	find_last_zero_index(char *line)
{
	int	i;
	int	save;

	i = 0;
	save = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '0')
			save = i;
		i++;
	}
	return (save);
}
