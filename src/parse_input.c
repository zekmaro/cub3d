/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:39:20 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/18 17:37:04 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_components(char **components)
{
	if (components)
	{
		free(components[0]);
		free(components[1]);
		free(components[2]);
		free(components);
	}
}

void	parse_color_components(char *line, int *r, int *g, int *b)
{
	char	**components;

	components = ft_split(line, ',');
	if (!components)
	{
		perror("Error\nFailed to split color components\n");
		exit(EXIT_FAILURE);
	}
	if (!components[0] || !components[1] || !components[2])
	{
		free_components(components);
		perror("Error\nInvalid color components\n");
		exit(EXIT_FAILURE);
	}
	*r = ft_atoi(components[0]);
	*g = ft_atoi(components[1]);
	*b = ft_atoi(components[2]);
	free_components(components);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		perror("Error\nInvalid color components\n");
		exit(EXIT_FAILURE);
	}
}

int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	parse_texture(t_vars *vars, char *line, char **texture)
{
	if (*texture)
	{
		perror("Error\nMultiple texture paths found\n");
		exit(EXIT_FAILURE);
	}
	while (*(line + 3) == ' ' || *(line + 3) == '\t' || *(line + 3) == '\n' \
		|| *(line + 3) == '\r' || *(line + 3) == '\f' || *(line + 3) == '\v')
		line++;
	*texture = ft_strdup(line + 3);
	if (!*texture)
		exit_with_error(vars, "Error\nFailed to allocate memory for texture\n");
}

void	parse_line(t_vars *vars, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[0]);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[1]);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[2]);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[3]);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color_components(line + 2, \
			&vars->floor_r, &vars->floor_g, &vars->floor_b);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color_components(line + 2, \
			&vars->ceiling_r, &vars->ceiling_g, &vars->ceiling_b);
	vars->floor_color = rgb_to_hex(vars->floor_r, vars->floor_g, vars->floor_b);
	vars->ceiling_color = rgb_to_hex(vars->ceiling_r, vars->ceiling_g, \
										vars->ceiling_b);
}
