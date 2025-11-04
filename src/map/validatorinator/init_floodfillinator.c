/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_floodfillinator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:23:11 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 13:49:03 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/validatorinator.h"
#include "utils/alloc.h"
#include <stdbool.h>
#include <stdlib.h>

static bool	alloc_list(void **list, size_t elem_size, int height)
{
	int	i;

	*list = (void *)malloc(sizeof(void *) * height);
	if (!*list)
		return (false);
	i = 0;
	while (i < height)
	{
		((char **)*list)[i] = (char *)malloc(elem_size);
		if (!((char **)*list)[i])
		{
			while (--i >= 0)
				free(((char **)*list)[i]);
			free(*list);
			return (false);
		}
		i++;
	}
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
	if (!alloc_list((void **)&ffi->visited, sizeof(bool) * ffi->width,
			ffi->height))
	{
		free(ffi);
		return (NULL);
	}
	return (ffi);
}
