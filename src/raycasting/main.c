/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:29:31 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/10 16:19:52 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	main(void)
{
	t_game	game;
	
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, win_width, win_height, "cub3d");
	game.img.img = mlx_new_image(game.mlx, win_width, win_height);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp,
			&game.img.line_length, &game.img.endian);
	init_player(&game.player, &game.map);
	printf("map.data = %p\n", game.map.data);
	render_frame(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_game, &game.img);
	mlx_loop(game.mlx);
	return (0);
}
