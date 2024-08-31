/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:04:34 by anarama           #+#    #+#             */
/*   Updated: 2024/08/30 23:39:59 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_vars_map(t_vars *vars)
{
	if (vars->map->grid)
		free_map(vars->map);
	free(vars->map);
}

void	free_vars_image(t_vars *vars)
{
	if (vars->image->mlx_img)
		mlx_destroy_image(vars->mlx->mlx, vars->image->mlx_img);
	free(vars->image);
}

void	free_vars_player(t_vars *vars)
{
	if (vars->player)
		free(vars->player);
}

void	free_vars_mlx(t_vars *vars)
{
	if (vars->mlx->win)
	{
		if (vars->mlx->win)
		{
			mlx_destroy_window(vars->mlx->mlx, vars->mlx->win);
			vars->mlx->win = NULL;
		}
		if (vars->mlx->mlx)
		{
			mlx_destroy_display(vars->mlx->mlx);
			free(vars->mlx->mlx);
			vars->mlx->mlx = NULL;
		}
		free(vars->mlx);
		vars->mlx = NULL;
	}
}

void	free_vars_line(t_vars *vars)
{
	if (vars->line)
		free(vars->line);
}
