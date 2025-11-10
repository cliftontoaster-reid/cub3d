/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:42:24 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/10 15:29:37 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	close_game(t_game *game)
{
	(void)game;
	exit(0);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_game(game);
	else if (keycode == XK_w)
		move_forward(&game->player, game->map.data);
	else if (keycode == XK_s)
		move_backward(&game->player, game->map.data);
	else if (keycode == XK_a)
		strafe_left(&game->player, game->map.data);
	else if (keycode == XK_d)
		strafe_right(&game->player, game->map.data);
    else if (keycode == XK_Left)
        rotate_left(&game->player);
    else if (keycode == XK_Right)
        rotate_right(&game->player);
    render_frame(game);
	return (0);
}
