/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:55:11 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/31 18:04:12 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player(t_vars *vars, int move_y, int move_x)
{
	int	x;
	int	y;
	int	save_x;
	int	save_y;

	x = vars->player->center_x + move_x * 5;
	y = vars->player->center_y + move_y * 5;
	save_x = x;
	save_y = y;
	rotate_around_point(vars, &x, &y);
	if (can_move(vars, save_y / vars->unit_size , save_x / vars->unit_size))
	{
		vars->player->y += move_y;
		vars->player->x += move_x;
	}
}

int	mouse_move(int x, int y, t_vars *vars)
{
	(void)y;
	vars->player->angle = (x / 360);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
		vars->image->mlx_img, 0, 0);
	return (0);
}

void	check_move_player(int keycode, t_vars *vars)
{
	int	move_x;
	int	move_y;

	move_x = 8;
	move_y = 8;
	if (keycode == W)
		move_player(vars, move_y * sin(vars->player->angle), \
			move_x * cos(vars->player->angle));
	else if (keycode == S)
		move_player(vars, -move_y * sin(vars->player->angle), \
			-move_x * cos(vars->player->angle));
	else if (keycode == D)
		move_player(vars, move_y * cos(vars->player->angle), \
			-move_x * sin(vars->player->angle));
	else if (keycode == A)
		move_player(vars, -move_y * cos(vars->player->angle), \
			move_x * sin(vars->player->angle));
	else if (keycode == KEY_LEFT)
		vars->player->angle -= M_PI / 90;
	else if (keycode == KEY_RIGHT)
		vars->player->angle += M_PI / 90;
}


int	animate_shooting(t_vars *vars)
{
	static int frame_count = 0; // Frame counter for animation

    if (!vars->player->shoot) // Check if animation should continue
        return (0);

    long elapsed_time;
    get_current_time(&vars->current_time);
    elapsed_time = get_elapsed_time(&vars->program_start, &vars->current_time);

    if (elapsed_time % 100 == 0)
    {
		if (frame_count == 2 && !vars->player->fire_done)
		{
			vars->player->fire_done = 1;
			frame_count = 0;
		}
        if (frame_count == 4) // Stop after 3 frames
        {
            vars->player->shoot = 0; // Reset shooting flag
            frame_count = 0;       // Reset frame counter
            return (0);
        }
		if (vars->player->fire_done)
        	update_sprite_frame(vars->player->gun);
        draw_map(vars);
		if (!vars->player->fire_done)
		{
			draw_fire(vars, 4.0);
			update_sprite_frame(vars->player->fire);
		}
        mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
        frame_count++;
    }
    return (0);
}

int	shoot_this_shit(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;

	if (button == MOUSE_CLICK_LEFT && !vars->player->shoot)
	{
		vars->player->shoot = 1;
		vars->player->fire_done = 0;      
	}
	return (0);             
}

void	handle_key(int keycode, t_vars *vars)
{
	check_move_player(keycode, vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		free_and_exit(vars);
	else
	{
		handle_key(keycode, vars);
		animate_shooting(vars);
	}
	return (0);
}
