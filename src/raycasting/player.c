/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:31:36 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/10 13:57:08 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_player(t_player *p, t_map *map)
{
	p->x = (double)map->player_start.x + 0.5;
	p->y = (double)map->player_start.y + 0.5;
	if (map->player_start_dir == PLAYER_DIR_EAST)
	{
		p->dir_x = 1.0;
		p->dir_y = 0.0;
		p->plane_x = 0.0;
		p->plane_y = PLANE_LEN;
	}
	else if (map->player_start_dir == PLAYER_DIR_WEST)
	{
		p->dir_x = -1.0;
		p->dir_y = 0.0;
		p->plane_x = 0.0;
		p->plane_y = -PLANE_LEN;
	}
	else if (map->player_start_dir == PLAYER_DIR_NORTH)
	{
		p->dir_x = 0.0;
		p->dir_y = -1.0;
		p->plane_x = -PLANE_LEN;
		p->plane_y = 0.0;
	}
	else
	{
		p->dir_x = 0.0;
		p->dir_y = 1.0;
		p->plane_x = PLANE_LEN;
		p->plane_y = 0.0;
	}
}

void	rotate_left(t_player *p)
{
	double old_dx;
	double old_px;
	double ang;

	ang = ROT_SPEED;
	old_dx = p->dir_x;
	old_px = p->plane_x;
	p->dir_x = p->dir_x * cos(ang) - p->dir_y * sin(ang);
	p->dir_y = old_dx * sin(ang) + p->dir_y * cos(ang);
	p->plane_x = p->plane_x * cos(ang) - p->plane_y * sin(ang);
	p->plane_y = old_px * sin(ang) + p->plane_y * cos(ang);
}

void	rotate_right(t_player *p)
{
double old_dx;
	double old_px;
	double ang;

	ang = -ROT_SPEED;
	old_dx = p->dir_x;
	old_px = p->plane_x;
	p->dir_x = p->dir_x * cos(ang) - p->dir_y * sin(ang);
	p->dir_y = old_dx * sin(ang) + p->dir_y * cos(ang);
	p->plane_x = p->plane_x * cos(ang) - p->plane_y * sin(ang);
	p->plane_y = old_px * sin(ang) + p->plane_y * cos(ang);
}
