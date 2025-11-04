/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:39:11 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 13:55:35 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//
#include "map/table.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
	if (map->north_wall_texture)
		free(map->north_wall_texture);
	if (map->south_wall_texture)
		free(map->south_wall_texture);
	if (map->west_wall_texture)
		free(map->west_wall_texture);
	if (map->east_wall_texture)
		free(map->east_wall_texture);
	free(map);
}
