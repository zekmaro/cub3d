/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:15:53 by anarama           #+#    #+#             */
/*   Updated: 2024/08/29 21:01:12 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_elem)
{
	if (new_elem == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_elem;
		return ;
	}
	new_elem->next = *lst;
	*lst = new_elem;
}
