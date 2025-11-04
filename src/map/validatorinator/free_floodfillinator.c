/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_floodfillinator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:21:23 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 13:57:22 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/validatorinator.h"
#include "utils/alloc.h"
#include <stdlib.h>

void	free_floodfillinator(t_floodfillinator *ffi)
{
	int	i;

	if (!ffi)
		return ;
	if (ffi->to_visit)
		vec_free(ffi->to_visit);
	if (ffi->visited)
	{
		i = 0;
		while (i < ffi->height)
		{
			if (ffi->visited[i])
				free(ffi->visited[i]);
			i++;
		}
		free(ffi->visited);
	}
	free(ffi);
}
