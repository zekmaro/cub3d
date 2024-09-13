/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_components.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:19:44 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 03:03:37 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_vars_image(t_vars *vars)
{
	if (vars->image->mlx_img)
		mlx_destroy_image(vars->mlx->mlx, vars->image->mlx_img);
	free(vars->image);
	vars->image = NULL;
}

void	free_vars_player(t_vars *vars)
{
	if (vars->player)
	{
		free(vars->player);
		vars->player = NULL;
	}
}

void	free_vars_mlx(t_vars *vars)
{
	if (vars->mlx)
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
	{
		free(vars->line);
		vars->line = NULL;
	}
}

void	free_vars_ray(t_vars *vars)
{
	if (vars->ray)
	{
		free(vars->ray);
		vars->ray = NULL;
	}
}
