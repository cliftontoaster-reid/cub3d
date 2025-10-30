/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:39:11 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 13:42:21 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
//
#include "map/table.h"

static bool	init_line(char **line, int width)
{
	int	j;

	*line = (char *)malloc(sizeof(char) * (width));
	if (!*line)
		return (false);
	j = 0;
	while (j < width)
	{
		(*line)[j] = ' ';
		j++;
	}
	return (true);
}

t_map	*create_map(int width, int height)
{
	t_map	*map;
	int		i;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = width;
	map->height = height;
	map->data = (char **)malloc(sizeof(char *) * height);
	if (!map->data)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < height)
	{
		if (!init_line(&map->data[i++], width))
		{
			free_map(map);
			return (NULL);
		}
	}
	return (map);
}
