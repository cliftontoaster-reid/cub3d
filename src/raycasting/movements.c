/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:26:05 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/17 15:22:08 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	move_forward(t_player *p, char **map)
{
	double nx;
	double ny;

	nx = p->x + p->dir_x * MOVE_SPEED;
	ny = p->y + p->dir_y * MOVE_SPEED;
	if (map[(int)ny][(int)nx] != '1')
	{
		p->x = nx;
		p->y = ny;
	}
}

void	move_backward(t_player *p, char **map)
{
	double nx;
	double ny;

	nx = p->x - p->dir_x * MOVE_SPEED;
	ny = p->y - p->dir_y * MOVE_SPEED;
	if (map[(int)ny][(int)nx] != '1')
	{
		p->x = nx;
		p->y = ny;
	}
}

void strafe_left(t_player *p, char **map)
{
	double nx;
	double ny;

	nx = p->x - p->plane_x * MOVE_SPEED;
	ny = p->y - p->plane_y * MOVE_SPEED;
	if (map[(int)ny][(int)nx] != '1')
	{
		p->x = nx;
		p->y = ny;
	}
}

void strafe_right(t_player *p, char **map)
{
	double nx;
	double ny;

	nx = p->x + p->plane_x * MOVE_SPEED;
	ny = p->y + p->plane_y * MOVE_SPEED;
	if (map[(int)ny][(int)nx] != '1')
	{
		p->x = nx;
		p->y = ny;
	}
}