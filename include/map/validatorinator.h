/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validatorinator.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:14:31 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/10 15:23:03 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map/table.h"
#include "utils/alloc.h"

typedef struct s_floodfillinator
{
	t_vec			*to_visit;
	bool			**visited;
	char			**map;
	int				width;
	int				start;
	int				height;
	const char		*map_path;
}					t_floodfillinator;

t_floodfillinator	*init_floodfillinator(t_map *map, const char *map_path);
bool				run_floodfillinator(t_floodfillinator *ffi,
						t_pointinator start);
void				free_floodfillinator(t_floodfillinator *ffi);
bool				is_map_valid(t_map *map, const char *map_path);
bool				is_map_string_validinator(t_map *map);
