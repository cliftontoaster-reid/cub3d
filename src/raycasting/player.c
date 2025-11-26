/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:31:36 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/26 14:07:53 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "raycasting.h"

static void	setorient(t_player *p, t_player_dir dir)
{
	ft_bzero(p, sizeof(t_player));
	if (dir == PLAYER_DIR_EAST)
	{
		p->dir_x = 1.0;
		p->plane_y = PLANE_LEN;
	}
	else if (dir == PLAYER_DIR_WEST)
	{
		p->dir_x = -1.0;
		p->plane_y = -PLANE_LEN;
	}
	else if (dir == PLAYER_DIR_NORTH)
	{
		p->dir_y = -1.0;
		p->plane_x = -PLANE_LEN;
	}
	else
	{
		p->dir_y = 1.0;
		p->plane_x = PLANE_LEN;
	}
}

bool	init_player(t_player *p, t_map *map)
{
	setorient(p, map->player_start_dir);
	p->x = (double)map->player_start.x + 0.5;
	p->y = (double)map->player_start.y + 0.5;
	return (true);
}

bool	rotate_left(t_player *p)
{
	double	old_dx;
	double	old_px;
	double	ang;

	ang = ROT_SPEED;
	old_dx = p->dir_x;
	old_px = p->plane_x;
	p->dir_x = p->dir_x * cos(ang) - p->dir_y * sin(ang);
	p->dir_y = old_dx * sin(ang) + p->dir_y * cos(ang);
	p->plane_x = p->plane_x * cos(ang) - p->plane_y * sin(ang);
	p->plane_y = old_px * sin(ang) + p->plane_y * cos(ang);
	return (true);
}

bool	rotate_right(t_player *p)
{
	double	old_dx;
	double	old_px;
	double	ang;

	ang = -ROT_SPEED;
	old_dx = p->dir_x;
	old_px = p->plane_x;
	p->dir_x = p->dir_x * cos(ang) - p->dir_y * sin(ang);
	p->dir_y = old_dx * sin(ang) + p->dir_y * cos(ang);
	p->plane_x = p->plane_x * cos(ang) - p->plane_y * sin(ang);
	p->plane_y = old_px * sin(ang) + p->plane_y * cos(ang);
	return (true);
}
