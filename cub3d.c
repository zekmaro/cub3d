/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:04:39 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/28 13:51:15 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_screen(t_vars *vars)
{
	vars->mlx->mlx = mlx_init();
	vars->mlx->win = mlx_new_window(vars->mlx->mlx, vars->mlx->window_width,
			vars->mlx->window_height, "Draw Grid");
	get_data_image(vars, vars->image, vars->mlx);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
			vars->image->mlx_img, 0, 0);
	mlx_hook(vars->mlx->win, 6, 1L << 6, mouse_move, vars);
	mlx_key_hook(vars->mlx->win, key_hook, vars);
	//mlx_hook(vars->mlx->win, 17, 0, (int (*)(void))free_and_exit, vars);
	mlx_loop(vars->mlx->mlx);
}

void	setup_player(t_vars *vars)
{
	vars->player->x = (vars->map->player_x * 64) + 64 / 2;
	vars->player->y = (vars->map->player_y * 64) + 64 / 2;
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	fd = 0;
	if (argc != 2)
	{
		perror("Usage: ./fdf <filename>\n");
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
	{
		exit(EXIT_FAILURE);
		//free_and_exit(&vars);
	}
	setup_player(&vars);
	print_map(vars.map);
	//initialise_map_vars(&vars);
	run_screen(&vars);
	return (0);
}