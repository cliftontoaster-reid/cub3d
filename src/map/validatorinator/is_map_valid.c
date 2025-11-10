/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:54:21 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/10 16:04:21 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map/validatorinator.h"
#include "messages.h"
#include "utils/alloc.h"
#include "utils/panic.h"
#include <stdio.h>

bool	is_map_valid(t_map *map, const char *map_path)
{
	t_floodfillinator	*ffi;
	t_pointinator		start;
	bool				result;
	t_pointinator		last_pos;

	ffi = init_floodfillinator(map, map_path);
	if (!ffi)
		return (false);
	start.x = map->player_start.x;
	start.y = map->player_start.y;
	result = run_floodfillinator(ffi, start);
	if (!result)
	{
		last_pos = *(t_pointinator *)vec_pop_back(ffi->to_visit);
		print_map_with_marker(last_pos.y, last_pos.x, ffi, ERR_MAP_NOTCLOSED);
	}
	free_floodfillinator(ffi);
	return (result);
}
