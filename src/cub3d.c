/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:04:39 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/10 16:02:44 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main_loop_hook(t_vars *vars)
{
	struct timeval	t;
	double			abc;

	get_current_time(&t);
	abc = (double)t.tv_sec + (double)t.tv_usec / 1000000;
	get_current_time(&vars->player->time1);
	handle_player_damaged_time(vars);
	update_enemy_list(vars->imp_list, 200, vars->map->imp_list_size);
	update_enemy_list(vars->caco_list, 200, vars->map->caco_list_size);
	update_position(vars);
	draw_sprite(vars);
	if (vars->player->shoot)
		animate_shooting(vars);
	search_for_player(vars);
	act_detected_enemies(vars);
	if (vars->player->is_damaged)
		draw_player_damaged(vars);
	get_current_time(&t);
	printf("diff: %1.12f\n", ((double)t.tv_sec \
		+ (double)t.tv_usec / 1000000) - abc);
	return (0);
}

void	run_screen(t_vars *vars)
{
	vars->mlx->mlx = mlx_init();
	if (!vars->mlx->mlx)
	{
		perror("Error\n");
		free_and_exit(vars);
	}
	vars->mlx->win = mlx_new_window(vars->mlx->mlx, vars->mlx->window_width, \
		vars->mlx->window_height, "Gestalt Cube3D");
	get_data_image(vars, vars->image, vars->mlx);
	initialise_textures(vars);
	initialise_sprites(vars);
	init_enemies(vars);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
		vars->image->mlx_img, 0, 0);
	reset_mouse_to_center(vars);
	mlx_hook(vars->mlx->win, 2, 1L << 0, key_press, vars);
	mlx_hook(vars->mlx->win, 3, 1L << 1, key_up, vars);
	mlx_mouse_hook(vars->mlx->win, shoot_entity, vars);
	mlx_hook(vars->mlx->win, 6, 1L << 6, mouse_move, vars);
	mlx_loop_hook(vars->mlx->mlx, main_loop_hook, vars);
	mlx_hook(vars->mlx->win, 17, 0, free_and_exit, vars);
	mlx_loop(vars->mlx->mlx);
}

void	setup_door(t_vars *vars)
{
	vars->door->center_x = vars->map->door_x * vars->unit_size \
		+ vars->unit_size / 2;
	vars->door->center_y = vars->map->door_y * vars->unit_size \
		+ vars->unit_size / 2;
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	if (argc != 2)
	{
		perror("Usage: ./cub3D [path]<filename>.cub\n");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Invalid file descriptor!\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(&vars, sizeof(t_vars));
	initialise_vars(&vars);
	if (!read_map(fd, vars.map, argv[1]))
		free_and_exit(&vars);
	init_enemy_lists(&vars);
	setup_player(&vars);
	setup_door(&vars);
	get_current_time(&vars.program_start);
	run_screen(&vars);
	return (0);
}
