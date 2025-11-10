/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:58:10 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/10 16:34:35 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define tile_size 1
# define step_size 0.05
# define MOVE_SPEED 0.10
# define ROT_SPEED 0.06
# define PLANE_LEN 0.66
# define win_width 800
# define win_height 600
# define FOV (M_PI / 3)

# include "map/table.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
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

typedef struct s_game
{
	t_data		img;
	t_player	player;
	t_map		map;
	void		*mlx;
	void		*win;
}				t_game;

/****** Render ******/
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_tile(t_data *img, int x, int start_y, int color);
void			draw_minimap(t_data *img, char **map, t_player *player);
void			draw_wall(t_data *img, int x, double dist);

/****** Raycasting ******/
double			cast_one_ray(t_player *player, t_map *map, double ray_dx,
					double ray_dy);
void			cast_all_rays(t_player *player, t_map *map, t_data *data);

/****** Player ******/
void			init_player(t_player *p, t_map *map);
void			move_forward(t_player *p, char **map);
void			move_backward(t_player *p, char **map);
void			strafe_left(t_player *p, char **map);
void			strafe_right(t_player *p, char **map);
void			rotate_left(t_player *p);
void			rotate_right(t_player *p);

/****** Hooks ******/
int				close_game(t_game *game);
int				handle_keypress(int keycode, t_game *game);
void			render_frame(t_game *game);
#endif
