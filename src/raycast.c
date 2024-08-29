/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:15:16 by iberegsz          #+#    #+#             */
/*   Updated: 2024/08/29 20:10:54 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void cast_ray(t_vars *vars, double ray_angle, int ray_id)
{
    double ray_x = vars->player->x;
    double ray_y = vars->player->y;
    double ray_dir_x = cos(ray_angle);
    double ray_dir_y = sin(ray_angle);
    double distance_to_wall = 0;

    while (1)
    {
        ray_x += ray_dir_x;
        ray_y += ray_dir_y;
        if (vars->map->grid[(int)(ray_y / vars->unit_size)][(int)(ray_x / vars->unit_size)] == '1')
        {
            distance_to_wall = sqrt(pow(ray_x - vars->player->x, 2) + pow(ray_y - vars->player->y, 2));
            break;
        }
    }

    int line_height = (int)(vars->mlx->window_height / distance_to_wall);
    int draw_start = -line_height / 2 + vars->mlx->window_height / 2;
    if (draw_start < 0) draw_start = 0;
    int draw_end = line_height / 2 + vars->mlx->window_height / 2;
    if (draw_end >= vars->mlx->window_height) draw_end = vars->mlx->window_height - 1;

    for (int y = draw_start; y < draw_end; y++)
    {
        put_pixel_to_image(vars, ray_id, y, WHITE);
    }
}

void raycast(t_vars *vars)
{
    int x;
    double fov = M_PI / 3;
    double angle_step = fov / vars->mlx->window_width;
    double start_angle = vars->player->angle - (fov / 2);

    x = 0;
    while (x < vars->mlx->window_width)
    {
        double ray_angle = start_angle + x * angle_step;
        cast_ray(vars, ray_angle, x);
        x++;
    }
}