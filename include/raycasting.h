/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:58:10 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/17 15:42:51 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define tile_size 1
# define step_size 0.05
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.03
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
}				t_game;

/****** Render ******/
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_tile(t_data *img, int x, int start_y, int color);
void			draw_minimap(t_data *img, char **map, t_player *player);
void			draw_wall(t_data *img, int x, double dist);
void			render_frame(t_game *game);

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
int				handle_keypress(t_game *game);
void			setup_hooks(t_game *game);

void			cleanup_game(t_game *game);
#endif
