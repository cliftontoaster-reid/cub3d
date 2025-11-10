/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:13:39 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/10 16:36:51 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double	cast_one_ray(t_player *player, t_map *map, double ray_dx, double ray_dy)
{
	double	rx;
	double	ry;
	double	dx;
	double	dy;
	double	distance;

	rx = player->x;
	ry = player->y;
	while ((int)rx >= 0 && (int)ry >= 0 && (int)rx < map->width
		&& (int)ry < map->height && map->data[(int)ry][(int)rx] != '1')
	{
		rx += ray_dx * step_size;
		ry += ray_dy * step_size;
		// my_mlx_pixel_put(img, (int)(x * tile_size), (int)(y * tile_size),
		// 	0x00FF00);
	}
	dx = rx - player->x;
	dy = ry - player->y;
	distance = sqrt(dx * dx + dy * dy);
	return (distance);
}

void	cast_all_rays(t_player *player, t_map *map, t_data *data)
{
	int		col;
	double	dist;
	double	camera_x;
	double	ray_dx;
	double	ray_dy;

	col = 0;
	while (col < win_width)
	{
		camera_x = 2.0 * (double)col / (double)win_width - 1.0;
		ray_dx = player->dir_x + player->plane_x * camera_x;
		ray_dy = player->dir_y + player->plane_y * camera_x;
		dist = cast_one_ray(player, map, ray_dx, ray_dy);
		draw_wall(data, col, dist);
		col++;
	}
}
