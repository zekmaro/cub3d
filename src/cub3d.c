/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:04:39 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/10 14:40:39 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

long	update_imp_time(t_vars *vars)
{
	long	elapsed_time;

	get_current_time(&vars->imp->time1);
	elapsed_time = get_elapsed_time(&vars->imp->time0, &vars->imp->time1);
	return (elapsed_time);
}

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
	printf("diff: %1.12f\n", ((double)t.tv_sec + (double)t.tv_usec / 1000000) - abc);
	return (0);
}

void	setup_imp(t_vars *vars, t_enemy *imp)
{
	imp->x = (imp->grid_x * vars->unit_size);
	imp->y = (imp->grid_y * vars->unit_size);
	imp->center_x = imp->x + vars->unit_size / 2;
	imp->center_y = imp->y + vars->unit_size / 2;
	imp->angle = -M_PI / 2;
	imp->rot_dir = 1;
	imp->fire_ball_x = imp->center_x;
	imp->fire_ball_y = imp->center_y;
	imp->health = 100;
	imp->is_dead = 0;
	imp->move_animation = ft_calloc(sizeof(t_img), 1);
	imp->death_animation = ft_calloc(sizeof(t_img), 1);
	imp->attack_animation = ft_calloc(sizeof(t_img), 1);
	imp->fire_ball = ft_calloc(sizeof(t_img), 1);
	get_current_time(&imp->time0);
	init_imp_sprites(vars, imp);
}

void	setup_caco(t_vars *vars, t_enemy *caco)
{
	caco->x = (caco->grid_x * vars->unit_size);
	caco->y = (caco->grid_y * vars->unit_size);
	caco->center_x = caco->x + vars->unit_size / 2;
	caco->center_y = caco->y + vars->unit_size / 2;
	caco->angle = -M_PI / 2;
	caco->rot_dir = 1;
	caco->fire_ball_x = caco->center_x;
	caco->fire_ball_y = caco->center_y;
	caco->health = 100;
	caco->is_dead = 0;
	caco->move_animation = ft_calloc(sizeof(t_img), 1);
	caco->death_animation = ft_calloc(sizeof(t_img), 1);
	caco->attack_animation = ft_calloc(sizeof(t_img), 1);
	caco->fire_ball = ft_calloc(sizeof(t_img), 1);
	get_current_time(&caco->time0);
	init_caco_sprites(vars, caco);
}

void	init_enemies(t_vars *vars)
{
	int	i;
	int	j;
	int	counter_imp;
	int	counter_caco;

	counter_imp = 0;
	counter_caco = 0;
	i = -1;
	while (vars->map->grid[++i])
	{
		j = -1;
		while (vars->map->grid[i][++j])
		{
			if (vars->map->grid[i][j] == 'M')
			{
				vars->imp_list[counter_imp].grid_x = j;
				vars->imp_list[counter_imp].grid_y = i;
				setup_imp(vars, &vars->imp_list[counter_imp]);
				counter_imp++;
			}
			else if (vars->map->grid[i][j] == 'C')
			{
				vars->caco_list[counter_caco].grid_x = j;
				vars->caco_list[counter_caco].grid_y = i;
				setup_caco(vars, &vars->caco_list[counter_caco]);
				counter_caco++;
			}
		}
	}
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

void	init_enemy_lists(t_vars *vars)
{
	vars->imp_list = ft_calloc(sizeof(t_enemy), vars->map->imp_list_size);
	vars->caco_list = ft_calloc(sizeof(t_enemy), vars->map->caco_list_size);
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
