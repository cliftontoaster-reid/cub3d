/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:36:18 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/06 13:46:37 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > 800 || y < 0 || y >= 600)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_tile(t_data *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_wall(t_data *img, int x, double dist)
{
	double	plane;
	int		wall_height;
	int		top;
	int		bottom;
	int		y;

	if (dist < 0.0001)
		dist = 0.0001;
	plane = (win_width / 2) / tan(FOV / 2);
	wall_height = (int)((tile_size * plane) / dist);
	top = (win_height / 2) - (wall_height / 2);
	bottom = (win_height / 2) + (wall_height / 2);
	if (top < 0)
		top = 0;
	if (bottom >= win_height)
		bottom = win_height - 1;
	y = top;
	while (y <= bottom)
	{
		my_mlx_pixel_put(img, x, y, 0xAAAAAA);
		y++;
	}
}

void	draw_minimap(t_data *img, char **map, t_player *player)
{
	int	row;
	int	col;
	int	color;
	int	x;
	int	y;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == '1')
				color = 0x888888;
			else
				color = 0x000000;
			draw_tile(img, col * tile_size, row * tile_size, color);
			col++;
		}
		row++;
	}
	x = (int)(player->x * tile_size);
	y = (int)(player->y * tile_size);
	my_mlx_pixel_put(img, x, y, 0xFF0000);
}
