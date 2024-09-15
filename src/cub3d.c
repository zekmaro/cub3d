/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:04:39 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/14 20:06:29 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main_loop_hook(t_vars *vars)
{
	struct timeval	t;

	reset_mouse_to_center(vars);
	get_current_time(&t);
	get_current_time(&vars->player->time1);
	handle_player_damaged_time(vars);
	get_current_time(&vars->door->time1);
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
	if (vars->door->draw && vars->offset < vars->unit_size)
		vars->offset += 4;
	else if (!vars->door->draw && vars->offset > 0)
		vars->offset -= 4;
	vars->door->time0 = vars->door->time1;
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, \
		vars->image->mlx_img, 0, 0);
	get_current_time(&t);
	return (0);
}

void	safe_init_mlx(t_vars *vars)
{
	vars->mlx->mlx = mlx_init();
	if (!vars->mlx->mlx)
	{
		free(vars->mlx);
		vars->mlx = NULL;
		exit_with_error(vars, "Failed to initialise mlx");
		exit(EXIT_FAILURE);
	}
	vars->mlx->win = mlx_new_window(vars->mlx->mlx, vars->mlx->window_width, \
		vars->mlx->window_height, "Gestalt DOOM Cube3D");
	if (!vars->mlx->win)
	{
		mlx_destroy_display(vars->mlx->mlx);
		free(vars->mlx->mlx);
		vars->mlx->mlx = NULL;
		free(vars->mlx);
		vars->mlx = NULL;
		exit_with_error(vars, "Failed to create window");
	}
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
	setup_door(vars, vars->door);
	printout_doors(vars);
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
	initialise_doors(&vars);
	init_enemy_lists(&vars);
	setup_player(&vars);
	get_current_time(&vars.program_start);
	run_screen(&vars);
	return (0);
}
