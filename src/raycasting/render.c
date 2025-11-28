/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:36:18 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/28 15:03:13 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "raycasting.h"
#include <sys/time.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
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
	scale = (double)(texture->height) / (double)(height);
	tex_y = (int)(tex_y * scale);
	addr = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bpp
				/ 8));
	color = *(unsigned int *)addr;
	return (color);
}

inline void	draw_tile(t_data *img, t_vec2i pos, t_vec2i size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			my_mlx_pixel_put(img, pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_wall(t_game *game, t_data *img, int x, t_rayhit dist)
{
	t_wall_ctx	c;

	if (dist.perp_dist < 0.0001)
		dist.perp_dist = 0.0001;
	c.plane = (double)WINDOW_WIDTH / 2.0 / tan(FOV / 2);
	c.wall_height = (int)((1.0 * c.plane) / (dist.perp_dist * TILE_SIZE));
	c.start = (WINDOW_HEIGHT / 2) - (c.wall_height / 2);
	c.top = c.start;
	c.bottom = (WINDOW_HEIGHT / 2) + (c.wall_height / 2);
	if (c.top < 0)
		c.top = 0;
	if (c.bottom >= WINDOW_HEIGHT)
		c.bottom = WINDOW_HEIGHT - 1;
	c.y = 0;
	while (c.y < c.top)
	{
		my_mlx_pixel_put(img, x, c.y, game->map.ceiling_color);
		c.y++;
	}
	while (c.y <= c.bottom)
	{
		c.colour = mlx_get_pixel(game, dist, c.y - c.start, c.wall_height);
		my_mlx_pixel_put(img, x, c.y, c.colour);
		c.y++;
	}
	while (c.y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(img, x, c.y, game->map.floor_color);
		c.y++;
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
			color = game->map.floor_color;
			if (game->map.data[row][col] == '1')
				color = game->map.ceiling_color;
			draw_tile(&game->img, (t_vec2i){col * TILE_SIZE * 2, row * TILE_SIZE
				* 2}, (t_vec2i){TILE_SIZE * 2, TILE_SIZE * 2}, color);
			col++;
		}
		row++;
	}
	col = (int)(game->player.x * TILE_SIZE * 2) - TILE_SIZE / 2;
	row = (int)(game->player.y * TILE_SIZE * 2) - TILE_SIZE / 2;
	draw_tile(&game->img, (t_vec2i){col - 2, row - 2}, (t_vec2i){4, 4},
		~game->map.ceiling_color);
}

void	render_frame(t_game *game)
{
	struct timeval	tv;
	int				fps;
	char			*fpstr;

	printf("\033[1A");
	printf("\033[J");
	gettimeofday(&tv, NULL);
	mlx_clear_window(game->mlx, game->win);
	memset(game->img.addr, 0, WINDOW_WIDTH * WINDOW_HEIGHT * 4);
	cast_all_rays(game, &game->player, &game->map, &game->img);
	draw_minimap(game);
	gettimeofday(&tv, NULL);
	while (tv.tv_sec * 1000 + tv.tv_usec / 1000 - game->last_frame_time < 16)
	{
		gettimeofday(&tv, NULL);
	}
	fps = 1000 / ((tv.tv_sec * 1000 + tv.tv_usec / 1000)
			- game->last_frame_time);
	printf("FPS: %d\n", fps);
	game->last_frame_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	fpstr = ft_itoa(fps);
	mlx_string_put(game->mlx, game->win, WINDOW_WIDTH - 80, 20,
		~game->map.ceiling_color, fpstr);
	free(fpstr);
}
