/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:31:36 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/06 11:59:56 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_player(t_player *player, t_map *map)
{
	player->x = map->player_start.x + 0.5;
	player->y = map->player_start.y + 0.5;
	player->dir = get_dir_angle(map->player_start_dir);
}

double	get_dir_angle(t_player_dir dir)
{
	if (dir == PLAYER_DIR_NORTH)
		return (M_PI / 2);
	if (dir == PLAYER_DIR_SOUTH)
		return (3 * M_PI / 2);
	if (dir == PLAYER_DIR_EAST)
		return (0);
	if (dir == PLAYER_DIR_WEST)
		return (M_PI);
	return (0);
}
