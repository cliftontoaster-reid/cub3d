/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_string_validinator.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:20:12 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/10 16:08:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map/validatorinator.h"
#include "messages.h"
#include "utils/panic.h"
#include <stdio.h>

static bool	is_empty(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < (size_t)map->height)
	{
		j = 0;
		while (j < (size_t)map->width)
		{
			if (map->data[i][j] != ' ')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_map_string_validinator(t_map *map)
{
	int		i;
	int		j;
	bool	found_robert_fitzroy_cavendish_smythe_3rd;

	found_robert_fitzroy_cavendish_smythe_3rd = false;
	if (is_empty(map))
	{
		print_map_with_marker_simple(-1, -1, map, ERR_MAP_EMPTY);
		return (false);
	}
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!ft_strchr(INCLUSIVE_MAP_CHARS "\n", map->data[i][j]))
			{
				print_map_with_marker_simple(i, j, map, ERR_MAP_INVALIDCHAR);
				return (false);
			}
			if (ft_strchr(RACIST_MAP_CHAR_PLAYER, map->data[i][j]))
			{
				if (found_robert_fitzroy_cavendish_smythe_3rd)
				{
					print_map_with_marker_simple(i, j, map,
						ERR_MAP_MULTIPLAYER);
					return (false);
				}
				found_robert_fitzroy_cavendish_smythe_3rd = true;
			}
			j++;
		}
		i++;
	}
	if (!found_robert_fitzroy_cavendish_smythe_3rd)
		print_map_with_marker_simple(-1, -1, map, ERR_MAP_NOPLAYER);
	return (found_robert_fitzroy_cavendish_smythe_3rd);
}
