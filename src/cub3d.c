/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:04:39 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/01 01:52:18 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	run_screen(t_vars *vars)
{
	vars->mlx->mlx = mlx_init();
	vars->mlx->win = mlx_new_window(vars->mlx->mlx, vars->mlx->window_width, \
		vars->mlx->window_height, "Gestalt Cube3D");
	get_data_image(vars, vars->image, vars->mlx);
	initialise_textures(vars);
	initialise_sprites(vars);
	update_sprite_frame(vars->animated_sprite);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
		vars->image->mlx_img, 0, 0);
	//mlx_hook(vars->mlx->win, 6, 1L << 6, mouse_move, vars);
	mlx_key_hook(vars->mlx->win, key_hook, vars);
	mlx_hook(vars->mlx->win, 17, 0, free_and_exit, vars);
	mlx_loop(vars->mlx->mlx);
}

int	game_loop(t_vars *vars)
{
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
		vars->image->mlx_img, 0, 0);
	return (0);
}

void	setup_player(t_vars *vars)
{
	vars->player->x = (vars->map->player_x * vars->unit_size) \
		+ vars->unit_size / 2;
	vars->player->y = (vars->map->player_y * vars->unit_size) \
		+ vars->unit_size / 2;
	vars->player->fov = M_PI / 3;
	if (vars->map->player_dir == 'N')
		vars->player->angle = -M_PI / 2;
	else if (vars->map->player_dir == 'W')
		vars->player->angle = -M_PI;
	if (vars->map->player_dir == 'S')
		vars->player->angle = -3 * M_PI / 2;
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
	setup_player(&vars);
	//print_map(vars.map);
	run_screen(&vars);
	return (0);
}
