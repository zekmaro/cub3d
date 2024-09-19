/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:39:20 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/19 19:15:06 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_color_components(char *line, int *r, int *g, int *b)
{
	char	**components;

	components = ft_split(line, ',');
	if (!components)
	{
		return (0);
	}
	check_valid_rgb(components, r, g, b);
	free_components(components);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		return (0);
	}
	return (1);
}

void	parse_texture(t_vars *vars, char *line, char **texture)
{
	if (*texture)
	{
		ft_putstr_fd("Error\nMultiple texture paths found\n", 2);
		exit(EXIT_FAILURE);
	}
	while (*(line + 3) == ' ' || *(line + 3) == '\t' || *(line + 3) == '\n' \
		|| *(line + 3) == '\r' || *(line + 3) == '\f' || *(line + 3) == '\v')
		line++;
	*texture = ft_strdup(line + 3);
	if (!*texture)
	{
		free(line);
		get_next_line(-1, NULL);
		exit_with_error(vars, "Error\nFailed to allocate memory for texture\n");
	}
}

void	parse_line(t_vars *vars, char *line)
{
	int	result;

	result = 1;
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[0]);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[1]);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[2]);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[3]);
	else if (ft_strncmp(line, "F ", 2) == 0)
		result = parse_color_components(line + 2, \
			&vars->floor_r, &vars->floor_g, &vars->floor_b);
	else if (ft_strncmp(line, "C ", 2) == 0)
		result = parse_color_components(line + 2, \
			&vars->ceiling_r, &vars->ceiling_g, &vars->ceiling_b);
	if (!result)
	{
		free(line);
		get_next_line(-1, NULL);
		free_and_exit(vars);
	}
	vars->floor_color = rgb_to_hex(vars->floor_r, vars->floor_g, vars->floor_b);
	vars->ceiling_color = rgb_to_hex(vars->ceiling_r, vars->ceiling_g, \
										vars->ceiling_b);
}
