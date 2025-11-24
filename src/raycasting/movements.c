/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:26:05 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/24 16:31:11 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	move_forward(t_player *p, char **map)
{
	double	nx;
	double	ny;
	double	margin;

	margin = 0.2;
	nx = p->x + p->dir_x * MOVE_SPEED;
	ny = p->y + p->dir_y * MOVE_SPEED;
	if (map[(int)(ny - margin)][(int)(nx - margin)] != '1' && map[(int)(ny
			- margin)][(int)(nx + margin)] != '1' && map[(int)(ny
			+ margin)][(int)(nx - margin)] != '1' && map[(int)(ny
			+ margin)][(int)(nx + margin)] != '1')
	{
		p->x = nx;
		p->y = ny;
	}
	else if (map[(int)(p->y - margin)][(int)(nx - margin)] != '1'
		&& map[(int)(p->y - margin)][(int)(nx + margin)] != '1'
		&& map[(int)(p->y + margin)][(int)(nx - margin)] != '1'
		&& map[(int)(p->y + margin)][(int)(nx + margin)] != '1')
		p->x = nx;
	else if (map[(int)(ny - margin)][(int)(p->x - margin)] != '1'
		&& map[(int)(ny - margin)][(int)(p->x + margin)] != '1' && map[(int)(ny
			+ margin)][(int)(p->x - margin)] != '1' && map[(int)(ny
			+ margin)][(int)(p->x + margin)] != '1')
		p->y = ny;
}

void	move_backward(t_player *p, char **map)
{
	double	nx;
	double	ny;
	double	margin;

	margin = 0.2;
	nx = p->x - p->dir_x * MOVE_SPEED;
	ny = p->y - p->dir_y * MOVE_SPEED;
	if (map[(int)(ny - margin)][(int)(nx - margin)] != '1' && map[(int)(ny
			- margin)][(int)(nx + margin)] != '1' && map[(int)(ny
			+ margin)][(int)(nx - margin)] != '1' && map[(int)(ny
			+ margin)][(int)(nx + margin)] != '1')
	{
		p->x = nx;
		p->y = ny;
	}
	else if (map[(int)(p->y - margin)][(int)(nx - margin)] != '1'
		&& map[(int)(p->y - margin)][(int)(nx + margin)] != '1'
		&& map[(int)(p->y + margin)][(int)(nx - margin)] != '1'
		&& map[(int)(p->y + margin)][(int)(nx + margin)] != '1')
		p->x = nx;
	else if (map[(int)(ny - margin)][(int)(p->x - margin)] != '1'
		&& map[(int)(ny - margin)][(int)(p->x + margin)] != '1' && map[(int)(ny
			+ margin)][(int)(p->x - margin)] != '1' && map[(int)(ny
			+ margin)][(int)(p->x + margin)] != '1')
		p->y = ny;
}

void	strafe_left(t_player *p, char **map)
{
	double	nx;
	double	ny;
	double	margin;

	margin = 0.2;
	nx = p->x - p->plane_x * MOVE_SPEED;
	ny = p->y - p->plane_y * MOVE_SPEED;
	if (map[(int)(ny - margin)][(int)(nx - margin)] != '1' && map[(int)(ny
			- margin)][(int)(nx + margin)] != '1' && map[(int)(ny
			+ margin)][(int)(nx - margin)] != '1' && map[(int)(ny
			+ margin)][(int)(nx + margin)] != '1')
	{
		p->x = nx;
		p->y = ny;
	}
	else if (map[(int)(p->y - margin)][(int)(nx - margin)] != '1'
		&& map[(int)(p->y - margin)][(int)(nx + margin)] != '1'
		&& map[(int)(p->y + margin)][(int)(nx - margin)] != '1'
		&& map[(int)(p->y + margin)][(int)(nx + margin)] != '1')
		p->x = nx;
	else if (map[(int)(ny - margin)][(int)(p->x - margin)] != '1'
		&& map[(int)(ny - margin)][(int)(p->x + margin)] != '1' && map[(int)(ny
			+ margin)][(int)(p->x - margin)] != '1' && map[(int)(ny
			+ margin)][(int)(p->x + margin)] != '1')
		p->y = ny;
}

void	strafe_right(t_player *p, char **map)
{
	double nx;
	double ny;
	double margin;

	margin = 0.2;
	nx = p->x + p->plane_x * MOVE_SPEED;
	ny = p->y + p->plane_y * MOVE_SPEED;
	if (map[(int)(ny - margin)][(int)(nx - margin)] != '1' && map[(int)(ny
			- margin)][(int)(nx + margin)] != '1' && map[(int)(ny
			+ margin)][(int)(nx - margin)] != '1' && map[(int)(ny
			+ margin)][(int)(nx + margin)] != '1')
	{
		p->x = nx;
		p->y = ny;
	}
	else if (map[(int)(p->y - margin)][(int)(nx - margin)] != '1'
		&& map[(int)(p->y - margin)][(int)(nx + margin)] != '1'
		&& map[(int)(p->y + margin)][(int)(nx - margin)] != '1'
		&& map[(int)(p->y + margin)][(int)(nx + margin)] != '1')
		p->x = nx;
	else if (map[(int)(ny - margin)][(int)(p->x - margin)] != '1'
		&& map[(int)(ny - margin)][(int)(p->x + margin)] != '1' && map[(int)(ny
			+ margin)][(int)(p->x - margin)] != '1' && map[(int)(ny
			+ margin)][(int)(p->x + margin)] != '1')
		p->y = ny;
}