/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:42:24 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/17 15:13:37 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	close_game(t_game *game)
{
	(void)game;
	// cleanup_game(game);
	exit(0);
	return (0);
}

int key_press(int key_code, t_game *game)
{
	if (key_code == XK_Escape)
		close_game(game);
	if (key_code == XK_w)
		game->keys.w = 1;
	if (key_code == XK_s)
		game->keys.s = 1;
	if (key_code == XK_a)
		game->keys.a = 1;
	if (key_code == XK_d)
		game->keys.d = 1;
	if (key_code == XK_Left)
		game->keys.left = 1;
	if (key_code == XK_Right)
		game->keys.right = 1;
	return (0);
} 

int key_release(int key_code, t_game *game)
{
	if (key_code == XK_w)
		game->keys.w = 0;
	if (key_code == XK_s)
		game->keys.s = 0;
	if (key_code == XK_a)
		game->keys.a = 0;
	if (key_code == XK_d)
		game->keys.d = 0;
	if (key_code == XK_Left)
		game->keys.left = 0;
	if (key_code == XK_Right)
		game->keys.right = 0;
	return (0);
}

int	handle_keypress(t_game *game)
{
	if (game->keys.w)
		move_forward(&game->player, game->map.data);
	if (game->keys.s)
		move_backward(&game->player, game->map.data);
	if (game->keys.a)
		strafe_left(&game->player, game->map.data);
	if (game->keys.d)
		strafe_right(&game->player, game->map.data);
    if (game->keys.left)
        rotate_left(&game->player);
    if (game->keys.right)
        rotate_right(&game->player);
    render_frame(game);
	return (0);
}

void setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, handle_keypress, game);
}
