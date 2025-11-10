/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:39:11 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/03 15:08:30 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
//
#include "map/table.h"

static bool	init_line(char **line, int width)
{
	int	j;

	*line = (char *)malloc(sizeof(char) * (width + 1));
	if (!*line)
		return (false);
	j = 0;
	while (j < width)
	{
		(*line)[j] = RACIST_MAP_CHAR_THE_DARK_EMPTY_VOID_OF_SPACE;
		j++;
	}
	(*line)[j] = '\0';
	return (true);
}

static void	init_options(t_map *map)
{
	map->player_start.x = -1;
	map->player_start.y = -1;
	map->player_start_dir = 0;
	map->north_wall_texture = NULL;
	map->south_wall_texture = NULL;
	map->west_wall_texture = NULL;
	map->east_wall_texture = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->start = 0;
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
	init_options(map);
	return (map);
}
