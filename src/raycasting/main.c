/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:29:31 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/06 14:36:48 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	main(void)
{
	void		*mlx;
	void		*win;
	t_data		data;
	t_map		map_data;
	t_player	player;
	char		*map[] = {"111111111111111111111111111111111111",
				"100000000000000000000000000000000001",
				"100000000000000000000000000000000001",
				"100000000000000000000000000000000001",
				"100000000000000000000000000000000001",
				"100000000000000000000000000000000001",
				"100000000000000000000000000000000001",
				"111111111111111111111111111111111111", NULL};

	mlx = mlx_init();
	win = mlx_new_window(mlx, win_width, win_height, "wassup");
	data.img = mlx_new_image(mlx, win_width, win_height);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
			&data.endian);
	init_player(&player, &map_data);
	// draw_minimap(&img, map, &player);
	cast_all_rays(&player, map, &data);
	mlx_put_image_to_window(mlx, win, data.img, 0, 0);
	// mlx_hook(win, 2, 1L << 0, handle_keypress, &data);
	mlx_loop(mlx);
	return (0);
}
