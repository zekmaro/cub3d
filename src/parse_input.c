/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:39:20 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/17 00:54:15 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_color_components(char *line, int *r, int *g, int *b)
{
	char	**components;

	components = ft_split(line, ',');
	if (!components)
	{
		perror("Failed to split color components");
		exit(EXIT_FAILURE);
	}
	printf("    Color components: %s, %s, %s\n", components[0], components[1], components[2]);
	if (!components[0] || !components[1] || !components[2])
	{
		free(components[0]);
		free(components[1]);
		free(components[2]);
		free(components);
		perror("Invalid color components");
		exit(EXIT_FAILURE);
	}
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		free(components[0]);
		free(components[1]);
		free(components[2]);
		free(components);
		perror("Invalid color components");
		exit(EXIT_FAILURE);
	}
	*r = ft_atoi(components[0]);
	*g = ft_atoi(components[1]);
	*b = ft_atoi(components[2]);
	printf("    Parsed color components: r: %d, g: %d, b: %d\n", *r, *g, *b);	
	free(components[0]);
	free(components[1]);
	free(components[2]);
	free(components);
}

int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	parse_texture(t_vars *vars, char *line, char **texture)
{
	if (*texture)
	{
		perror("Multiple texture paths found");
		exit(EXIT_FAILURE);
	}
	while (*(line + 3) == ' ' || *(line + 3) == '\t' || *(line + 3) == '\n' \
		|| *(line + 3) == '\r' || *(line + 3) == '\f' || *(line + 3) == '\v')
		line++;
	*texture = ft_strdup(line + 3);
	if (!*texture)
		exit_with_error(vars, "Failed to allocate memory for texture");
	printf("    Texture path: %s\n", *texture);
}

void	parse_line(t_vars *vars, char *line)
{
	printf("  Parsing line: '%s'\n", line);
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
	printf("    Floor color: hex: %x dec: %d\n", vars->floor_color, vars->floor_color);
	vars->ceiling_color = rgb_to_hex(vars->ceiling_r, vars->ceiling_g, vars->ceiling_b);
	printf("    Ceiling color: hex: %x dec: %d\n", vars->ceiling_color, vars->ceiling_color);
	printf("      Reference. Brown color is dec: %d hex: %x \n", BROWN, BROWN);
	printf("    texture_names[0]: %s\n", vars->texture_names[0]);
	printf("    texture_names[1]: %s\n", vars->texture_names[1]);
	printf("    texture_names[2]: %s\n", vars->texture_names[2]);
	printf("    texture_names[3]: %s\n", vars->texture_names[3]);
}
