/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_cell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:47:27 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 14:59:12 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/table.h"
#include "utils/panic.h"

char	get_map_cell(t_map *map, int x, int y)
{
	if (!is_inbounds(map, x, y))
		panic("get_map_cell: coordinates out of bounds", __FILE__, __LINE__);
	return (map->data[y][x]);
}
