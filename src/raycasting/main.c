/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:29:31 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/04 13:28:41 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_player	player;
	char		*map[] = {"111111111111111111111111111111111111",
				"100000000000000000000000000000000001",
				"100000000000000000000000000000000001",
				"100000000000000000000000000000000001",
				"100000000000000000000000000000000001",
				"100000000000000000000000000000000001",
				"100000000000000000000000000000000001",
				"111111111111111111111111111111111111", NULL};

	/* 	double distance; */
	mlx = mlx_init();
	win = mlx_new_window(mlx, win_width, win_height, "wassup");
	img.img = mlx_new_image(mlx, win_width, win_height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
			&img.endian);
	player.x = 3.5;
	player.y = 3.5;
	player.dir = 0;
	// draw_minimap(&img, map, &player);
	cast_all_rays(&player, map, &img);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
