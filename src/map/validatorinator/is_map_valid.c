/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:54:21 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/10 11:26:14 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/validatorinator.h"

static bool is_all_accessible(t_floodfillinator *ffi)
{
	int x;
	int y;

	y = 0;
	while (y < ffi->height)
	{
		x = 0;
		while (x < ffi->width)
		{
			if (ffi->map[y][x] == '0' || ffi->visited[y][x] == false)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool is_map_valid(t_map *map)
{
	t_floodfillinator *ffi;
	t_pointinator start;
	bool result;

	ffi = init_floodfillinator(map);
	if (!ffi)
		return (false);
	start.x = map->player_start.x;
	start.y = map->player_start.y;
	result = run_floodfillinator(ffi, start);
	result = result && is_all_accessible(ffi);
	free_floodfillinator(ffi);
	return (result);
}
