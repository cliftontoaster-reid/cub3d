/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validatorinator.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:14:31 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 11:17:18 by lfiorell@st      ###   ########.fr       */
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
	int				height;
}					t_floodfillinator;

t_floodfillinator	*init_floodfillinator(t_map *map);
bool				run_floodfillinator(t_floodfillinator *ffi,
						t_pointinator start);
void				free_floodfillinator(t_floodfillinator *ffi);
bool				is_map_string_validinator(const char *map_str);
