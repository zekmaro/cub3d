/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:04:58 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/22 16:56:51 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

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

int	check_valid_rgb(char **components, int *r, int *g, int *b)
{
	char *str_r;
	char *str_g;
	char *str_b;

	if (!components)
		return (0);
	str_r = ft_strtrim(components[0], " ");
	str_g = ft_strtrim(components[1], " ");
	str_b = ft_strtrim(components[2], " ");
	if (!str_r || !str_g || !str_b)
		return (free(str_r), free(str_g), free(str_b), 0);
	*r = ft_atoi(str_r);
	*g = ft_atoi(str_g);
	*b = ft_atoi(str_b);
	if (!check_input(str_r, *r)
		|| !check_input(str_g, *g)
		|| !check_input(str_b, *b))
		return (0);
	return (free(str_r), free(str_g), free(str_b), 1);
}
