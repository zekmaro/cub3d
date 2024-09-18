/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:04:58 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/18 23:36:43 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_close(t_vars *vars, int fd)
{
	if (close(fd) == -1)
	{
		exit_with_error(vars, "Error\nClose failed\n");
	}
}

int	check_input(char *str, int num)
{
	char	*check;

	check = ft_itoa(num);
	if (!check || ft_strncmp(check, str, ft_strlen(str)) != 0)
	{
		free(check);
		return (0);
	}
	free(check);
	return (1);
}
