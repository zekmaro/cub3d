/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:04:58 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/19 21:07:20 by iberegsz         ###   ########.fr       */
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

int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	free_components(char **components)
{
	if (components)
	{
		free(components[0]);
		free(components[1]);
		free(components[2]);
		free(components);
	}
}

void	check_valid_rgb(char **components, int *r, int *g, int *b)
{
	*r = ft_atoi(components[0]);
	*g = ft_atoi(components[1]);
	*b = ft_atoi(components[2]);
	if (!check_input(components[0], *r)
		|| !check_input(components[1], *g)
		|| !check_input(components[2], *b))
	{
		free_components(components);
		ft_putstr_fd("Error\nInvalid color components\n", 2);
		exit(EXIT_FAILURE);
	}
}
