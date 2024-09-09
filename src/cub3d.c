/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:04:39 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/07 23:29:24 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <mlx.h>

long	update_imp_time(t_vars *vars)
{
	long	elapsed_time;

	get_current_time(&vars->imp->time1);
	elapsed_time = get_elapsed_time(&vars->imp->time0, &vars->imp->time1);
	return (elapsed_time);
}


int	key_press(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		free_and_exit(vars);
	if (keycode == W)
		vars->keys.w = 1;
	if (keycode == S)
		vars->keys.s = 1;
	if (keycode == A)
		vars->keys.a = 1;
	if (keycode == D)
		vars->keys.d = 1;
	if (keycode == SPACE)
		vars->keys.space = 1;
	if (keycode == KEY_LEFT)
		vars->keys.left = 1;
	if (keycode == KEY_RIGHT)
		vars->keys.right = 1;
	return (0);
}

int	key_up(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		free_and_exit(vars);
	if (keycode == W)
		vars->keys.w = 0;
	if (keycode == S)
		vars->keys.s = 0;
	if (keycode == A)
		vars->keys.a = 0;
	if (keycode == D)
		vars->keys.d = 0;
	if (keycode == SPACE)
		vars->keys.space = 0;
	if (keycode == KEY_LEFT)
		vars->keys.left = 0;
	if (keycode == KEY_RIGHT)
		vars->keys.right = 0;
	return (0);
}

int	player_damaged_enemy(t_vars *vars, t_enemy *enemy)
{
	return (abs(enemy->fire_ball_x - vars->player->center_x) < 20
		&& abs(enemy->fire_ball_y - vars->player->center_y) < 20
		&& !vars->player->is_damaged);
}

void	update_enemy_list(t_enemy *enemy_list, long delay, int size)
{
	long enemy_elapsed_time;
	int i = 0;

	while (i < size)
	{
		get_current_time(&enemy_list[i].time1);
		enemy_elapsed_time = get_elapsed_time(&enemy_list[i].time0, &enemy_list[i].time1);
		if (enemy_elapsed_time > delay)
		{
			if (enemy_list[i].current_animation == enemy_list[i].death_animation
				&& enemy_list[i].current_animation->current_frame
				== enemy_list[i].current_animation->frame_count - 1)
			{
				enemy_list[i].is_dead = 1;
				enemy_list[i].center_x = -100;
				enemy_list[i].center_y = -100;
			}
			update_sprite_frame(enemy_list[i].current_animation);
			if (enemy_list[i].current_animation == enemy_list[i].attack_animation
			&& enemy_list[i].current_animation->current_frame
			== enemy_list[i].current_animation->frame_count - 1)
				enemy_list[i].current_animation = enemy_list[i].move_animation;
			enemy_list[i].time0 = enemy_list[i].time1;
		}
		i++;
	}
}

void	update_damaged_player(t_vars *vars)
{
	vars->player->is_damaged = 1;
	vars->player->health -= 20;
	get_current_time(&vars->player->time0);
	system("aplay ./assets/player_pain.wav -q &");
	if (vars->player->health == 0)
	{
		printf("GAME OVER!\n");
		system("aplay ./assets/player_dead.wav -q &");
		free_and_exit(vars);
	}
}

void	enemy_shoot(t_enemy *enemy, int vector_x, int vector_y, int vector)
{
	if (enemy->health > 0)
		enemy->current_animation = enemy->attack_animation;
	enemy->fire_delta_y = (vector_y * vector_y / vector) / 10;
	if (vector_y < 0)
		enemy->fire_delta_y *= -1;
	enemy->fire_delta_x = (vector_x * vector_x / vector) / 10;
	if (vector_x < 0)
		enemy->fire_delta_x *= -1;
	enemy->shoot_ball = 1;
}

void	handle_enemy_shot(t_vars *vars, t_enemy * enemy)
{
	if (player_damaged_enemy(vars, enemy))
	{
		update_damaged_player(vars);
		enemy->fire_ball_y = 0;
		enemy->fire_ball_x = 0;
	}
	else
	{
		enemy->fire_ball_y += enemy->fire_delta_y;
		enemy->fire_ball_x += enemy->fire_delta_x;		
	}
}

void	enemy_act(t_vars *vars, t_enemy *enemy)
{
	int vector_x = vars->player->center_x - enemy->center_x;
	int vector_y = vars->player->center_y - enemy->center_y;
	int vector = sqrt(vector_x * vector_x + vector_y * vector_y);
	enemy->center_x += vector_x / 40;
	enemy->center_y += vector_y / 40;
	if (!enemy->shoot_ball)
	{
		enemy_shoot(enemy, vector_x, vector_y, vector);
	}
	if (is_wall(vars, enemy->fire_ball_y, enemy->fire_ball_x))
	{
		enemy->fire_ball_y = enemy->center_y;
		enemy->fire_ball_x = enemy->center_x;
		enemy->shoot_ball = 0;
	}
	else
	{
		handle_enemy_shot(vars, enemy);
	}
	enemy->detected_player = 0;
}

void	handle_player_damaged_time(t_vars *vars)
{
	long time_player_damaged;
	
	time_player_damaged = get_elapsed_time(&vars->player->time0, &vars->player->time1);
	if (time_player_damaged > 500)
	{
		vars->player->is_damaged = 0;
	}
}

void	search_for_player(t_vars *vars)
{
	int i = 0;
	while (i < vars->map->imp_list_size)
	{
		if (!vars->imp_list[i].detected_player)
			vars->imp_list[i].angle += M_PI / 10 * vars->imp_list[i].rot_dir;
		i++;
	}
	i = 0;
	while (i < vars->map->caco_list_size)
	{
		if (!vars->caco_list[i].detected_player)
			vars->caco_list[i].angle += M_PI / 10 * vars->caco_list[i].rot_dir;
		i++;
	}
}

void	act_detected_enemies(t_vars *vars)
{
	int i = 0;

	while (i < vars->map->imp_list_size)
	{
		if (vars->imp_list[i].detected_player)
			enemy_act(vars, &vars->imp_list[i]);
		i++;
	}
	i = 0;
	while (i < vars->map->caco_list_size)
	{
		if (vars->caco_list[i].detected_player)
			enemy_act(vars, &vars->caco_list[i]);
		i++;
	}
}

int	main_loop_hook(t_vars *vars)
{
	struct timeval t;
	double abc;

	get_current_time(&t);
	abc = (double)t.tv_sec + (double)t.tv_usec / 1000000;
	get_current_time(&vars->player->time1);
	handle_player_damaged_time(vars);
	update_enemy_list(vars->imp_list, 200, vars->map->imp_list_size);
	update_enemy_list(vars->caco_list, 200, vars->map->caco_list_size);
	if (!vars->player->shoot)
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
	int i = 0;
	int j = 0;
	int counter_imp = 0;
	int counter_caco = 0;

	while (vars->map->grid[i])
	{
		j = 0;
		while (vars->map->grid[i][j])
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
			j++;
		}
		i++;
	}
}

void	run_screen(t_vars *vars)
{
	vars->mlx->mlx = mlx_init();
	vars->mlx->win = mlx_new_window(vars->mlx->mlx, vars->mlx->window_width, \
		vars->mlx->window_height, "Gestalt Cube3D");
	get_data_image(vars, vars->image, vars->mlx);
	initialise_textures(vars);
	initialise_sprites(vars);
	init_enemies(vars);
	draw_door(vars);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
		vars->image->mlx_img, 0, 0);
	reset_mouse_to_center(vars);
	mlx_hook(vars->mlx->win, 2, 1L << 0, key_press, vars);
	mlx_hook(vars->mlx->win, 3, 1L << 1, key_up, vars);
	mlx_mouse_hook(vars->mlx->win, shoot_this_shit, vars);
	mlx_hook(vars->mlx->win, 6, 1L << 6, mouse_move, vars);
	mlx_loop_hook(vars->mlx->mlx, main_loop_hook, vars);
	mlx_hook(vars->mlx->win, 17, 0, free_and_exit, vars);
	mlx_loop(vars->mlx->mlx);
}

void	setup_player(t_vars *vars)
{
	double	plane_length;

	vars->player->x = (vars->map->player_x * vars->unit_size) \
		+ vars->unit_size / 2;
	vars->player->y = (vars->map->player_y * vars->unit_size) \
		+ vars->unit_size / 2;
	vars->player->fov = M_PI / 3;
	if (vars->map->player_dir == 'N')
		vars->player->angle = -M_PI / 2;
	else if (vars->map->player_dir == 'W')
		vars->player->angle = -M_PI;
	else if (vars->map->player_dir == 'S')
		vars->player->angle = -3 * M_PI / 2;
	else if (vars->map->player_dir == 'E')
		vars->player->angle = 0;
	vars->player->dir_x = cos(vars->player->angle);
	vars->player->dir_y = sin(vars->player->angle);
	plane_length = tan(vars->player->fov / 2);
	vars->player->plane_x = -vars->player->dir_y * plane_length;
	vars->player->plane_y = vars->player->dir_x * plane_length;
	vars->player->health = 100;
}

void	setup_door(t_vars *vars)
{
	vars->door->center_x = vars->map->door_x * vars->unit_size + vars->unit_size / 2;
	vars->door->center_y = vars->map->door_y * vars->unit_size + vars->unit_size / 2;
}

void	init_lists(t_vars *vars)
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
	init_lists(&vars);
	setup_player(&vars);
	setup_door(&vars);
	//setup_caco(&vars);
	get_current_time(&vars.program_start);
	//print_map(vars.map);
	run_screen(&vars);
	return (0);
}

// get_current_time(&vars.program_start);
//print_map(vars.map);
// run_screen(&vars);