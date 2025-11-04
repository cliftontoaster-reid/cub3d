/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_floodfillinator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:23:11 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 15:26:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/validatorinator.h"
#include "utils/alloc.h"
#include <stdbool.h>
#include <stdlib.h>

static bool	alloc_list(bool ***list, size_t elem_size, int height, int width)
{
	int		i;
	bool	**rows;

	(void)elem_size;
	rows = (bool **)malloc(sizeof(bool *) * height);
	if (!rows)
		return (false);
	i = 0;
	while (i < height)
	{
		rows[i] = (bool *)calloc((size_t)width, sizeof(bool));
		if (!rows[i])
		{
			while (--i >= 0)
				free(rows[i]);
			free(rows);
			return (false);
		}
		i++;
	}
	*list = rows;
	return (true);
}

t_floodfillinator	*init_floodfillinator(t_map *map)
{
	t_floodfillinator	*ffi;

	ffi = (t_floodfillinator *)malloc(sizeof(t_floodfillinator));
	if (!ffi)
		return (NULL);
	ffi->width = map->width;
	ffi->height = map->height;
	ffi->map = map->data;
	ffi->to_visit = vec_init(sizeof(t_pointinator));
	if (!ffi->to_visit)
	{
		free(ffi);
		return (NULL);
	}
	if (!alloc_list(&ffi->visited, sizeof(bool) * ffi->width, ffi->height,
			ffi->width))
	{
		free(ffi);
		vec_free(ffi->to_visit);
		return (NULL);
	}
	return (ffi);
}
