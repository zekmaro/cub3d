/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:45:13 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/16 11:42:16 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_door_list(t_vars *vars, t_door *door_list, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		if (door_list[i].open && door_list[i].offset < vars->unit_size)
			door_list[i].offset += 8;
		else if (!door_list[i].open && door_list[i].offset > 0)
			door_list[i].offset -= 8;
	}
}
