/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:13:39 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/04 13:21:07 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	cast_one_ray(t_player *player, char **map, double ray_angle,
		t_data *img)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	distance;

	x = player->x;
	y = player->y;
	while (map[(int)y][(int)x] != '1')
	{
		x += cos(ray_angle) * step_size;
		y += sin(ray_angle) * step_size;
		my_mlx_pixel_put(img, (int)(x * tile_size), (int)(y * tile_size),
			0x00FF00);
	}
	dx = x - player->x;
	dy = y - player->y;
	distance = sqrt(dx * dx + dy * dy);
	return (distance);
}

void	cast_all_rays(t_player *player, char **map, t_data *data)
{
	int		i;
	double	dist;
	double	ray_angle;
	double	angle_step;

	i = 0;
	ray_angle = player->dir - (FOV / 2);
	angle_step = FOV / (double)win_width;
	while (i < win_width)
	{
		dist = cast_one_ray(player, map, ray_angle, data);
		draw_wall(data, i, dist);
		ray_angle += angle_step;
		i++;
	}
}
