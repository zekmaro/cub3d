/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:04:39 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/18 17:00:40 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main_loop_hook(t_vars *vars)
{
	reset_mouse_to_center(vars);
	get_current_time(&vars->player->time1);
	handle_player_damaged_time(vars);
	check_objects_to_draw(vars);
	update_enemy_list(vars->imp_list, 200, vars->map->imp_list_size);
	update_enemy_list(vars->caco_list, 300, vars->map->caco_list_size);
	update_enemy_frames(vars->boss, 200);
	search_for_player(vars);
	act_detected_enemies(vars);
	update_position(vars);
	draw_map(vars);
	if (vars->player->shoot)
		animate_shooting(vars);
	if (vars->player->is_damaged)
		draw_player_damaged(vars);
	draw_minimap(vars);
	draw_player(vars, RED);
	update_door_list(vars, vars->doors, vars->map->num_doors);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, \
		vars->image->mlx_img, 0, 0);
	return (0);
}

void	run_screen(t_vars *vars)
{
	safe_init_mlx(vars);
	get_data_image(vars, vars->image, vars->mlx);
	initialise_textures(vars);
	initialise_sprites(vars);
	init_imp_animation(vars);
	init_caco_animation(vars);
	init_enemies(vars);
	init_boss(vars);
	init_doors(vars);
	setup_door(vars, vars->doors);
	setup_boss(vars, vars->boss);
	reset_mouse_to_center(vars);
	mlx_hook(vars->mlx->win, 2, 1L << 0, key_press, vars);
	mlx_hook(vars->mlx->win, 3, 1L << 1, key_up, vars);
	mlx_hook(vars->mlx->win, 6, 1L << 6, mouse_move, vars);
	mlx_hook(vars->mlx->win, 17, 0, free_and_exit, vars);
	mlx_mouse_hook(vars->mlx->win, shoot_entity, vars);
	mlx_loop_hook(vars->mlx->mlx, main_loop_hook, vars);
	mlx_loop(vars->mlx->mlx);
}

int	validate_and_open_file(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		exit_with_error(NULL, "Error\nUsage: ./cub3D [path]<filename>.cub\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nInvalid file descriptor!\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	replace_space_with_one(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while ((size_t)j < ft_strlen(map->grid[i]))
		{
			if (map->grid[i][j] == ' ')
				map->grid[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;
	int		readed_lines;
	char	*line_left;

	line_left = NULL;
	fd = validate_and_open_file(argc, argv);
	ft_bzero(&vars, sizeof(t_vars));
	initialise_vars(&vars);
	readed_lines = parse_file_paths_and_colors(fd, &vars, &line_left);
	if (!read_map(fd, vars.map, argv[1], &line_left, readed_lines))
		exit_with_error(&vars, "Error\nFailed to read map\n");
	replace_space_with_one(vars.map);
	initialise_doors(&vars);
	init_enemy_lists(&vars);
	setup_player(&vars);
	get_current_time(&vars.program_start);
	run_screen(&vars);
	return (0);
}
