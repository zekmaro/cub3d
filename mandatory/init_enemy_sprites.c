/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy_sprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:00:30 by iberegsz          #+#    #+#             */
/*   Updated: 2024/09/13 19:01:17 by iberegsz         ###   ########.fr       */
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

void	init_boss_sprite(t_vars *vars, t_animation *boss_animation)
{
	const char	*boss_move_frames[] = {"./assets/cydem_walk1.xpm", \
		"./assets/cydem_walk2.xpm", "./assets/cydem_walk3.xpm", \
		"./assets/cydem_walk4.xpm", NULL};
	const char	*boss_death_frames[] = {"./assets/cydem_dies1.xpm", \
		"./assets/cydem_dies2.xpm", "./assets/cydem_dies3.xpm", \
		"./assets/cydem_dies4.xpm", "./assets/cydem_dies5.xpm", \
		"./assets/cydem_dies6.xpm", "./assets/cydem_dies7.xpm", \
		"./assets/cydem_dies8.xpm", "./assets/cydem_dies9.xpm", NULL};
	const char	*boss_attack_frames[] = {"./assets/cydem_atck1.xpm", \
		"./assets/cydem_atck2.xpm", NULL};
	const char	*boss_fire_ball_frames[] = {"./assets/cydem_rocket.xpm", NULL};

	initialise_enemy_textures(vars, boss_animation->move, boss_move_frames);
	initialise_enemy_textures(vars, boss_animation->death, boss_death_frames);
	initialise_enemy_textures(vars, boss_animation->attack, boss_attack_frames);
	initialise_enemy_textures(vars, boss_animation->bullet, \
		boss_fire_ball_frames);
}
