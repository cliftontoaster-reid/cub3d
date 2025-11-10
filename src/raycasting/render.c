/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:36:18 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/10 16:46:25 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > win_width || y < 0 || y >= win_height)
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
	plane = (double)win_width / 2.0 / tan(FOV / 2);
	wall_height = (int)((1.0 * plane) / (dist * tile_size));
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

void	render_frame(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	memset(game->img.addr, 0, win_width * win_height * 4);
	cast_all_rays(&game->player, &game->map, &game->img);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
