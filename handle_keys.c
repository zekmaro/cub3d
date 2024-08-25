/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:55:11 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/25 20:45:19 by andrejarama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

int	player_inside_map(t_vars *vars, int x, int y)
{
	return (x < vars->map->width
		&& y < vars->map->height);
}

int	can_move(t_vars *vars, int y, int x)
{
	if (player_inside_map(vars, x, y))
	{
		if (vars->map->grid[y][x] == '1')
			return (0);
		return (1);
	}
	else
		return (0);
}

void	move_player(t_vars *vars, int move_y, int move_x)
{
	int x;
	int y;
	int player_center_x;
	int player_center_y;

	player_center_x = vars->player->x + (8 / 2);
	player_center_y = vars->player->y + (8 / 2);
	x = (player_center_x + move_x) / 64;
	y = (player_center_y + move_y) / 64;
	if (can_move(vars, y, x))
	{
		vars->player->y += move_y;
		vars->player->x += move_x;	
	}
}

int mouse_move(int x, int y, t_vars *vars)
{
    // Example: Print the mouse position to the console
    printf("Mouse moved to: x = %d, y = %d\n", x, y);

    // Here you can add code to update your game state based on mouse movement

    return (0);
}


void	check_move_player(int keycode, t_vars *vars)
{
	int move_x;
	int move_y;

	move_x = 8;
	move_y = 8;
	if (keycode == W)
	{
		move_player(vars, -move_y, 0);
	}
	else if (keycode == S)
	{
		move_player(vars, move_y, 0);
	}
	else if (keycode == D)
	{
		move_player(vars, 0, move_x);
	}
	else if (keycode == A)
	{
		move_player(vars, 0, -move_x);
	}
}

void	handle_key(int keycode, t_vars *vars)
{
	check_move_player(keycode, vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
	{
		exit(1);
		//free_and_exit(vars);
	}
	else
	{
		clean_screen(vars);
		handle_key(keycode, vars);
		draw_map(vars);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
			vars->image->mlx_img, 0, 0);	
	}
	return (0);
}