/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:13:39 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/10 16:43:17 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double	cast_one_ray(t_player *player, t_map *map, double ray_dx, double ray_dy)
{
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	perp_dist;

	map_x = (int)player->x;
	map_y = (int)player->y;
	delta_x = fabs(1.0 / ray_dx);
	delta_y = fabs(1.0 / ray_dy);
	if (ray_dx < 0)
	{
		step_x = -1;
		side_x = (player->x - map_x) * delta_x;
	}
	else
	{
		step_x = 1;
		side_x = (map_x + 1.0 - player->x) * delta_x;
	}
	if (ray_dy < 0)
	{
		step_y = -1;
		side_y = (player->y - map_y) * delta_y;
	}
	else
	{
		step_y = 1;
		side_y = (map_y + 1.0 - player->y) * delta_y;
	}
	while (1)
	{
		if (side_x < side_y)
		{
			side_x += delta_x;
			map_x += step_x;
			perp_dist = (map_x - player->x + (1 - step_x) / 2) / ray_dx;
		}
		else
		{
			side_y += delta_y;
			map_y += step_y;
			perp_dist = (map_y - player->y + (1 - step_y) / 2) / ray_dy;
		}
		if (map_x < 0 || map_y < 0 || map_x >= map->width
			|| map_y >= map->height || map->data[map_y][map_x] == '1')
			break ;
	}
	return (perp_dist);
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
