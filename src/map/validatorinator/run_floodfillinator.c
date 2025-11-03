/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_floodfillinator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:26:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/03 15:07:16 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/validatorinator.h"

static void	push_pos(t_floodfillinator *ffi, int x, int y)
{
	t_pointinator	pos;

	if (x < 0 || x >= ffi->width || y < 0 || y >= ffi->height)
		return ;
	if (ffi->visited[y][x])
		return ;
	pos.x = x;
	pos.y = y;
	vec_push_back_absent(ffi->to_visit, &pos);
}

bool	run_floodfillinator(t_floodfillinator *ffi, t_pointinator start)
{
	t_pointinator	current;
	char			cell;

	push_pos(ffi, start.x, start.y);
	while (ffi->to_visit->size > 0)
	{
		current = *(t_pointinator *)vec_pop_back(ffi->to_visit);
		if (ffi->visited[current.y][current.x])
			continue ;
		ffi->visited[current.y][current.x] = true;
		cell = ffi->map[current.y][current.x];
		if (cell == '1')
			continue ;
		if (cell == RACIST_MAP_CHAR_THE_DARK_EMPTY_VOID_OF_SPACE)
			return (false);
		if (current.x == 0 || current.x == ffi->width - 1 || current.y == 0
			|| current.y == ffi->height - 1)
			return (false);
		push_pos(ffi, current.x + 1, current.y);
		push_pos(ffi, current.x - 1, current.y);
		push_pos(ffi, current.x, current.y + 1);
		push_pos(ffi, current.x, current.y - 1);
	}
	return (true);
}
