/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:36:18 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/24 17:32:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include <sys/time.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > win_width || y < 0 || y >= win_height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	mlx_get_pixel(t_game *game, t_rayhit dist, int tex_y, int height)
{
	t_data	*texture;
	char	*addr;
	int		color;
	int		tex_x;
	double	scale;

	if (dist.side == 0)
		texture = game->north;
	else if (dist.side == 1)
		texture = game->south;
	else if (dist.side == 2)
		texture = game->west;
	else
		texture = game->east;
	tex_x = (int)(dist.hit_x * (double)(texture->width));
	// scale the height accordingly
	scale = (double)(texture->height) / (double)(height);
	tex_y = (int)(tex_y * scale);
	addr = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bpp
				/ 8));
	color = *(unsigned int *)addr;
	return (color);
}

inline void	draw_tile(t_data *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < tile_size * 2)
	{
		j = 0;
		while (j < tile_size * 2)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_wall(t_game *game, t_data *img, int x, t_rayhit dist)
{
	double	plane;
	int		wall_height;
	int		top;
	int		bottom;
	int		y;
	int		colour;
	int		start;

	if (dist.perp_dist < 0.0001)
		dist.perp_dist = 0.0001;
	plane = (double)win_width / 2.0 / tan(FOV / 2);
	wall_height = (int)((1.0 * plane) / (dist.perp_dist * tile_size));
	start = (win_height / 2) - (wall_height / 2);
	top = start;
	bottom = (win_height / 2) + (wall_height / 2);
	if (top < 0)
		top = 0;
	if (bottom >= win_height)
		bottom = win_height - 1;
	y = 0;
	while (y < top)
	{
		my_mlx_pixel_put(img, x, y, game->map.ceiling_color);
		y++;
	}
	while (y <= bottom)
	{
		colour = mlx_get_pixel(game, dist, y - start, wall_height);
		my_mlx_pixel_put(img, x, y, colour);
		y++;
	}
	while (y < win_height)
	{
		my_mlx_pixel_put(img, x, y, game->map.floor_color);
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	int	row;
	int	col;
	int	color;

	row = 0;
	while (row < game->map.height)
	{
		col = 0;
		while (game->map.data[row][col])
		{
			color = 0x000000;
			if (game->map.data[row][col] == '1')
				color = 0x888888;
			draw_tile(&game->img, col++ * tile_size * 2, row * tile_size * 2,
				color);
		}
		row++;
	}
	col = (int)(game->player.x * tile_size * 2) - tile_size / 2;
	row = (int)(game->player.y * tile_size * 2) - tile_size / 2;
	draw_tile(&game->img, col + 2, row, 0xFF0000);
	draw_tile(&game->img, col - 2, row, 0xFF0000);
	draw_tile(&game->img, col, row + 2, 0xFF0000);
	draw_tile(&game->img, col, row - 2, 0xFF0000);
}

void	render_frame(t_game *game)
{
	struct timeval	tv;
	int				fps;

	// Remove the last 3 lines with ansi and print spaces to overwrite
	printf("\033[3A");
	printf("\033[J");
	gettimeofday(&tv, NULL);
	mlx_clear_window(game->mlx, game->win);
	memset(game->img.addr, 0, win_width * win_height * 4);
	cast_all_rays(game, &game->player, &game->map, &game->img);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	gettimeofday(&tv, NULL);
	while (tv.tv_sec * 1000 + tv.tv_usec / 1000 - game->last_frame_time < 16)
	{
		gettimeofday(&tv, NULL);
	}
	// Calculate and print FPS using last_frame_time
	fps = 1000 / ((tv.tv_sec * 1000 + tv.tv_usec / 1000)
			- game->last_frame_time);
	printf("FPS: %d\n", fps);
	game->last_frame_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
