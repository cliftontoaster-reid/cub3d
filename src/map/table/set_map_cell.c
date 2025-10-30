/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_cell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:13:15 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 14:59:31 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/table.h"
#include "utils/panic.h"

void	set_map_cell(t_map *map, int x, int y, char value)
{
	if (!is_inbounds(map, x, y))
		panic("set_map_cell: coordinates out of bounds", __FILE__, __LINE__);
	map->data[y][x] = value;
}
