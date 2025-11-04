/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:54:21 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 12:54:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/validatorinator.h"

bool	is_map_valid(t_map *map)
{
	t_floodfillinator	*ffi;
	t_pointinator		start;
	bool				result;

	ffi = init_floodfillinator(map);
	if (!ffi)
		return (false);
	start.x = map->player_start.x;
	start.y = map->player_start.y;
	result = run_floodfillinator(ffi, start);
	free_floodfillinator(ffi);
	return (result);
}
