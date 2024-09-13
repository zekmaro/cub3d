/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:14:05 by anarama           #+#    #+#             */
/*   Updated: 2024/09/13 14:31:08 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_imp_sprite(t_vars *vars, t_animation *imp_animation)
{
	const char	*imp_move_frames[] = {"./assets/imp_walk1.xpm", \
		"./assets/imp_walk2.xpm", "./assets/imp_walk3.xpm",
		"./assets/imp_walk4.xpm", NULL};
	const char	*imp_death_frames[] = {"./assets/imp_dies1.xpm", \
		"./assets/imp_dies2.xpm", "./assets/imp_dies3.xpm", \
		"./assets/imp_dies4.xpm", "./assets/imp_dies5.xpm",	NULL};
	const char	*imp_attack_frames[] = {"./assets/imp_attack1.xpm", \
		"./assets/imp_attack2.xpm",	"./assets/imp_attack3.xpm",	NULL};
	const char	*imp_fire_ball_frames[] = {"./assets/imp_fire1.xpm", \
		"./assets/imp_fire2.xpm", NULL};

	initialise_enemy_textures(vars, imp_animation->move, imp_move_frames);
	initialise_enemy_textures(vars, imp_animation->death, imp_death_frames);
	initialise_enemy_textures(vars, imp_animation->attack, imp_attack_frames);
	initialise_enemy_textures(vars, imp_animation->bullet, \
		imp_fire_ball_frames);
}

void	init_caco_sprite(t_vars *vars, t_animation *caco_animation)
{
	const char	*caco_move_frames[] = {"./assets/cacodemon1.xpm", \
		"./assets/caco_walk1.xpm", "./assets/caco_walk2.xpm", \
		"./assets/caco_walk3.xpm", "./assets/caco_walk4.xpm", \
		"./assets/caco_walk5.xpm", "./assets/caco_walk6.xpm", NULL};
	const char	*caco_death_frames[] = {"./assets/caco_dies1.xpm", \
		"./assets/caco_dies2.xpm", "./assets/caco_dies3.xpm", \
		"./assets/caco_dies4.xpm", "./assets/caco_dies5.xpm", NULL};
	const char	*caco_attack_frames[] = {"./assets/cacodemon2.xpm", \
		"./assets/cacodemon3.xpm", "./assets/cacodemon4.xpm", NULL};
	const char	*caco_fire_ball_frames[] = {"./assets/caco_fire1.xpm", NULL};

	initialise_enemy_textures(vars, caco_animation->move, caco_move_frames);
	initialise_enemy_textures(vars, caco_animation->death, caco_death_frames);
	initialise_enemy_textures(vars, caco_animation->attack, caco_attack_frames);
	initialise_enemy_textures(vars, caco_animation->bullet, \
		caco_fire_ball_frames);
}

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
