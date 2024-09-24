/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_animated_frames_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 02:15:59 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/24 16:57:52 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_animated_frames(t_img **frames, int count)
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
				free(tmp->mlx_img);
			free(tmp);
		}
		i++;
	}
	free(frames);
}
