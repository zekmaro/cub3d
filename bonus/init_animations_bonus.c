/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:14:05 by anarama           #+#    #+#             */
/*   Updated: 2024/09/24 16:59:58 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_imp_animation(t_vars *vars)
{
	t_animation	*imp_animation;

	if (vars == NULL)
		return ;
	imp_animation = (t_animation *)(malloc(sizeof(t_animation)));
	if (!imp_animation)
	{
		exit_with_error(vars, \
			"Error\nFailed to allocate memory for imp animation\n");
		return ;
	}
	vars->imp_animation = imp_animation;
	vars->imp_animation->move = ft_calloc(sizeof(t_img), 1);
	vars->imp_animation->death = ft_calloc(sizeof(t_img), 1);
	vars->imp_animation->attack = ft_calloc(sizeof(t_img), 1);
	vars->imp_animation->bullet = ft_calloc(sizeof(t_img), 1);
	if (!vars->imp_animation->move || !vars->imp_animation->death || \
		!vars->imp_animation->attack || !vars->imp_animation->bullet)
		exit_with_error(vars, \
			"Error\nFailed to allocate memory for imp animation\n");
	init_imp_sprite(vars, vars->imp_animation);
}

void	init_caco_animation(t_vars *vars)
{
	t_animation	*caco_animation;

	if (vars == NULL)
		return ;
	caco_animation = (t_animation *)(malloc(sizeof(t_animation)));
	if (!caco_animation)
	{
		exit_with_error(vars, \
			"Error\nFailed to allocate memory for caco animation\n");
		return ;
	}
	vars->caco_animation = caco_animation;
	vars->caco_animation->move = ft_calloc(sizeof(t_img), 1);
	vars->caco_animation->death = ft_calloc(sizeof(t_img), 1);
	vars->caco_animation->attack = ft_calloc(sizeof(t_img), 1);
	vars->caco_animation->bullet = ft_calloc(sizeof(t_img), 1);
	if (!vars->caco_animation->move || !vars->caco_animation->death || \
		!vars->caco_animation->attack || !vars->caco_animation->bullet)
		exit_with_error(vars, \
			"Error\nFailed to allocate memory for caco animation\n");
	init_caco_sprite(vars, vars->caco_animation);
}

void	init_cyber_demon_animation(t_vars *vars)
{
	t_animation	*boss_animation;

	if (vars == NULL)
		return ;
	boss_animation = (t_animation *)(malloc(sizeof(t_animation)));
	if (!boss_animation)
	{
		exit_with_error(vars, \
			"Error\nFailed to allocate memory for boss animation");
		return ;
	}
	vars->boss_animation = boss_animation;
	vars->boss_animation->move = ft_calloc(sizeof(t_img), 1);
	vars->boss_animation->death = ft_calloc(sizeof(t_img), 1);
	vars->boss_animation->attack = ft_calloc(sizeof(t_img), 1);
	vars->boss_animation->bullet = ft_calloc(sizeof(t_img), 1);
	if (!vars->boss_animation->move || !vars->boss_animation->death || \
		!vars->boss_animation->attack || !vars->boss_animation->bullet)
		exit_with_error(vars, \
			"Error\nFailed to allocate memory for boss animation");
	init_boss_sprite(vars, vars->boss_animation);
}
