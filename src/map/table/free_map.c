/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:39:11 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 14:55:04 by lfiorell@st      ###   ########.fr       */
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
	free(map);
}
