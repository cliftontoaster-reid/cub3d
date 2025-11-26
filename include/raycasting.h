/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:58:10 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/26 14:51:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#define TILE_SIZE 1
#define STEP_SIZE 0.05
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.05
#define PLANE_LEN 0.66
#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1000
#define FOV 1.0471975511965977461542144610931676280657231331250352736583148

#include "map/table.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;

	int			width;
	int			height;
}				t_data;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_game
{
	t_data		img;
	t_player	player;
	t_map		map;
	t_keys		keys;
	void		*mlx;
	void		*win;

	t_data		*north;
	t_data		*south;
	t_data		*east;
	t_data		*west;

	long long	last_frame_time;
}				t_game;

typedef struct s_rayhit
{
	int			map_x;
	int			map_y;
	int			side;
	double		perp_dist;
	double		hit_x;
}				t_rayhit;

typedef struct s_vec2d
{
	double		x;
	double		y;
}				t_vec2d;

typedef struct s_vec2i
{
	int			x;
	int			y;
}				t_vec2i;

typedef struct s_ray_ctx
{
	t_vec2d		delta;
	t_vec2d		side;
	t_vec2i		upos;
	t_vec2i		step;
	int			hit_vertical;
}				t_ray_ctx;

typedef struct s_wall_ctx
{
	double		plane;
	int			wall_height;
	int			top;
	int			bottom;
	int			y;
	int			colour;
	int			start;
}				t_wall_ctx;

/****** Render ******/
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_tile(t_data *img, t_vec2i pos, t_vec2i size, int color);
void			draw_minimap(t_game *game);
void			draw_wall(t_game *game, t_data *img, int x, t_rayhit dist);
void			render_frame(t_game *game);
bool			load_textures(t_game *game, t_map *map);

/****** Raycasting ******/
void			cast_all_rays(t_game *game, t_player *player, t_map *map,
					t_data *data);

/****** Player ******/
bool			init_player(t_player *p, t_map *map);
bool			move_forward(t_player *p, char **map);
bool			move_backward(t_player *p, char **map);
bool			strafe_left(t_player *p, char **map);
bool			strafe_right(t_player *p, char **map);
bool			rotate_player(t_player *p, double angle);
bool			rotate_left(t_player *p);
bool			rotate_right(t_player *p);

/****** Hooks ******/
int				close_game(t_game *game);
int				handle_keypress(t_game *game);
void			setup_hooks(t_game *game);

void			cleanup_game(t_game *game);
