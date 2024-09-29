/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_animated_frames.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 02:15:59 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/29 17:37:00 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_animated_frames(t_vars *vars, t_img **frames, int count)
{
	int		i;
	t_img	*tmp;

	if (frames == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		tmp = frames[i];
		if (tmp != NULL)
		{
			if (tmp->mlx_img != NULL)
				mlx_destroy_image(vars->mlx->mlx, tmp->mlx_img);
			free(tmp);
		}
		i++;
	}
	free(frames);
}
