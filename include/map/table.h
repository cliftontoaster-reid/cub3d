/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:32:14 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 14:59:15 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>

typedef struct s_map
{
	int		width;
	int		height;
	char	**data;
}			t_map;

t_map		*create_map(int width, int height);
void		free_map(t_map *map);
bool		is_inbounds(t_map *map, int x, int y);
char		get_map_cell(t_map *map, int x, int y);
void		set_map_cell(t_map *map, int x, int y, char value);

t_map		*map_from_str(const char *content);