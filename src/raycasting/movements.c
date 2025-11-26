/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:26:05 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/26 14:09:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

#define MARGIN 0.2

static inline int	can_move(char **map, double x, double y)
{
	return (map[(int)(y - MARGIN)][(int)(x - MARGIN)] != '1' && map[(int)(y
			- MARGIN)][(int)(x + MARGIN)] != '1' && map[(int)(y
			+ MARGIN)][(int)(x - MARGIN)] != '1' && map[(int)(y
			+ MARGIN)][(int)(x + MARGIN)] != '1');
}

bool	move_forward(t_player *p, char **map)
{
	double	nx;
	double	ny;

	nx = p->x + p->dir_x * MOVE_SPEED;
	ny = p->y + p->dir_y * MOVE_SPEED;
	if (can_move(map, nx, ny))
	{
		p->x = nx;
		p->y = ny;
		return (true);
	}
	else if (can_move(map, nx, p->y))
	{
		p->x = nx;
		return (true);
	}
	else if (can_move(map, p->x, ny))
	{
		p->y = ny;
		return (true);
	}
	return (false);
}

bool	move_backward(t_player *p, char **map)
{
	double	nx;
	double	ny;

	nx = p->x - p->dir_x * MOVE_SPEED;
	ny = p->y - p->dir_y * MOVE_SPEED;
	if (can_move(map, nx, ny))
	{
		p->x = nx;
		p->y = ny;
		return (true);
	}
	else if (can_move(map, nx, p->y))
	{
		p->x = nx;
		return (true);
	}
	else if (can_move(map, p->x, ny))
	{
		p->y = ny;
		return (true);
	}
	return (false);
}

bool	strafe_left(t_player *p, char **map)
{
	double	nx;
	double	ny;

	nx = p->x - p->plane_x * MOVE_SPEED;
	ny = p->y - p->plane_y * MOVE_SPEED;
	if (can_move(map, nx, ny))
	{
		p->x = nx;
		p->y = ny;
		return (true);
	}
	else if (can_move(map, nx, p->y))
	{
		p->x = nx;
		return (true);
	}
	else if (can_move(map, p->x, ny))
	{
		p->y = ny;
		return (true);
	}
	return (false);
}

bool	strafe_right(t_player *p, char **map)
{
	double	nx;
	double	ny;

	nx = p->x + p->plane_x * MOVE_SPEED;
	ny = p->y + p->plane_y * MOVE_SPEED;
	if (can_move(map, nx, ny))
	{
		p->x = nx;
		p->y = ny;
		return (true);
	}
	else if (can_move(map, nx, p->y))
	{
		p->x = nx;
		return (true);
	}
	else if (can_move(map, p->x, ny))
	{
		p->y = ny;
		return (true);
	}
	return (false);
}
