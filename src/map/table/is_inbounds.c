/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_inbounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:46:53 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 14:59:26 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
//
#include "map/table.h"

bool	is_inbounds(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width)
		return (false);
	if (y < 0 || y >= map->height)
		return (false);
	return (true);
}
