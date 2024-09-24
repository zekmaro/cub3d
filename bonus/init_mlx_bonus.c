/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:53:33 by anarama           #+#    #+#             */
/*   Updated: 2024/09/24 17:00:26 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialise_mlx(t_vars *vars)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)(malloc(sizeof(t_mlx)));
	if (!mlx)
	{
		exit_with_error(vars, "Error\nFailed to allocate memory for mlx\n");
		return ;
	}
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->window_height = 1080;
	mlx->window_width = 1920;
	vars->mlx = mlx;
}

void	safe_init_mlx(t_vars *vars)
{
	vars->mlx->mlx = mlx_init();
	if (!vars->mlx->mlx)
	{
		get_next_line(-1, NULL);
		free_and_exit(vars);
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
		exit_with_error(vars, "Error\nFailed to create window\n");
	}
}
