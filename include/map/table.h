/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:32:14 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/10 15:57:03 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <sys/types.h>

#define RACIST_MAP_CHAR_WALL '1'
#define RACIST_MAP_CHAR_EMPTY '0'
#define RACIST_MAP_CHAR_THE_DARK_EMPTY_VOID_OF_SPACE ' '
#define RACIST_MAP_CHAR_PLAYER "NSEW"

#define INCLUSIVE_MAP_CHARS "01NSEW "

typedef struct s_pointinator
{
	int				x;
	int				y;
}					t_pointinator;

typedef enum e_player_dir
{
	PLAYER_DIR_NORTH = 'N',
	PLAYER_DIR_SOUTH = 'S',
	PLAYER_DIR_EAST = 'E',
	PLAYER_DIR_WEST = 'W'
}					t_player_dir;

typedef struct s_map
{
	int				width;
	int				start;
	int				height;
	char			**data;

	t_pointinator	player_start;
	t_player_dir	player_start_dir;
	char			*north_wall_texture;
	char			*south_wall_texture;
	char			*west_wall_texture;
	char			*east_wall_texture;
	int				floor_color;
	int				ceiling_color;
	const char		*map_path;
}					t_map;

t_map				*create_map(int width, int height);
void				free_map(t_map *map);
bool				is_inbounds(t_map *map, int x, int y);
char				get_map_cell(t_map *map, int x, int y);
void				set_map_cell(t_map *map, int x, int y, char value);

t_map				*map_from_str(const char *content, const char *map_path,
						int start);
bool				parse_options(t_map *map, const char **lines, int count);

t_map				*read_map(const char *fullcontent, const char *path);