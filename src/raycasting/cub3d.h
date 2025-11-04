/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:58:10 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/04 13:21:19 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define tile_size 10
# define step_size 0.05
# define win_width 800
# define win_height 600
# define FOV (M_PI / 3)

# include "../../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
}			t_player;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_tile(t_data *img, int x, int start_y, int color);
void		draw_minimap(t_data *img, char **map, t_player *player);
void		draw_wall(t_data *img, int x, double dist);

double		cast_one_ray(t_player *player, char **map, double ray_angle,
				t_data *img);
void		cast_all_rays(t_player *player, char **map, t_data *data);
#endif
