/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:39:20 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/28 14:49:26 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_color_components(char *line, int *r, int *g, int *b)
{
	char	**components;
	int		split_size;
	int		flag;

	if (count_commas(line) != 2)
		return (0);
	components = ft_split(line, ',');
	split_size = get_split_size(components);
	if (split_size != 3)
	{
		free_split(components);
		return (0);
	}
	flag = check_valid_rgb(components, r, g, b);
	free_components(components);
	if (!flag)
		return (0);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

void	parse_texture(t_vars *vars, char *line, char **texture)
{
	char	*temp;

	if (*texture)
		handle_gnl_error_msg(vars, line, \
			"Error\nMultiple texture paths found\n");
	while (*(line + 3) == ' ' || *(line + 3) == '\t' || *(line + 3) == '\n' \
		|| *(line + 3) == '\r' || *(line + 3) == '\f' || *(line + 3) == '\v')
		line++;
	*texture = ft_strdup(line + 3);
	if (!*texture)
		handle_gnl_error_msg(vars, line, \
			"Error\nFailed to allocate memory for texture\n");
	temp = ft_strtrim(*texture, " ");
	if (!temp)
		handle_gnl_error_msg(vars, line, \
			"Error\nFailed to allocate memory for texture\n");
	free(*texture);
	*texture = temp;
	vars->num_path_color_lines++;
}

static int	parse_path_and_color_line(t_vars *vars, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[0]);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[1]);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[2]);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(vars, line, &vars->texture_names[3]);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (vars->num_path_color_lines++, \
			parse_color_components(line + 2, \
			&vars->floor_r, &vars->floor_g, &vars->floor_b));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (vars->num_path_color_lines++, \
			parse_color_components(line + 2, \
			&vars->ceiling_r, &vars->ceiling_g, &vars->ceiling_b));
	else
		return (0);
	return (1);
}

int	parse_line(t_vars *vars, char *line)
{
	int	result;

	result = parse_path_and_color_line(vars, line);
	if (!result)
		return (0);
	vars->floor_color = rgb_to_hex(vars->floor_r, \
		vars->floor_g, vars->floor_b);
	vars->ceiling_color = rgb_to_hex(vars->ceiling_r, \
		vars->ceiling_g, vars->ceiling_b);
	return (1);
}
