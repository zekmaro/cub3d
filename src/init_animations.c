/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:14:05 by anarama           #+#    #+#             */
/*   Updated: 2024/09/13 19:01:13 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_imp_animation(t_vars *vars)
{
	t_animation	*imp_animation;

	imp_animation = (t_animation *)(malloc(sizeof(t_animation)));
	vars->imp_animation = imp_animation;
	vars->imp_animation->move = ft_calloc(sizeof(t_img), 1);
	vars->imp_animation->death = ft_calloc(sizeof(t_img), 1);
	vars->imp_animation->attack = ft_calloc(sizeof(t_img), 1);
	vars->imp_animation->bullet = ft_calloc(sizeof(t_img), 1);
	init_imp_sprite(vars, vars->imp_animation);
}

void	init_caco_animation(t_vars *vars)
{
	t_animation	*caco_animation;

	caco_animation = (t_animation *)(malloc(sizeof(t_animation)));
	vars->caco_animation = caco_animation;
	vars->caco_animation->move = ft_calloc(sizeof(t_img), 1);
	vars->caco_animation->death = ft_calloc(sizeof(t_img), 1);
	vars->caco_animation->attack = ft_calloc(sizeof(t_img), 1);
	vars->caco_animation->bullet = ft_calloc(sizeof(t_img), 1);
	init_caco_sprite(vars, vars->caco_animation);
}

void	init_cyber_demon_animation(t_vars *vars)
{
	t_animation	*boss_animation;

	boss_animation = (t_animation *)(malloc(sizeof(t_animation)));
	vars->boss_animation = boss_animation;
	vars->boss_animation->move = ft_calloc(sizeof(t_img), 1);
	vars->boss_animation->death = ft_calloc(sizeof(t_img), 1);
	vars->boss_animation->attack = ft_calloc(sizeof(t_img), 1);
	vars->boss_animation->bullet = ft_calloc(sizeof(t_img), 1);
	init_boss_sprite(vars, vars->boss_animation);
}
