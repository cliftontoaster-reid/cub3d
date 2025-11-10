/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_from_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:27:10 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/10 15:58:32 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map/table.h"
#include "map/validatorinator.h"
#include "utils/panic.h"
#include <stdlib.h>

static int	count_lines(const char *content)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && content[i - 1] != '\n')
		count++;
	return (count);
}

static int	max_width(const char *content)
{
	int	max_width;
	int	current_width;
	int	i;

	max_width = 0;
	current_width = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
		{
			if (current_width > max_width)
				max_width = current_width;
			current_width = 0;
		}
		else
			current_width++;
		i++;
	}
	if (current_width > max_width)
		max_width = current_width;
	return (max_width);
}

static void	copy_data(t_map *map, const char *content)
{
	int	line;
	int	col;
	int	i;

	line = 0;
	col = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
		{
			line++;
			col = 0;
		}
		else
		{
			set_map_cell(map, col, line, content[i]);
			col++;
		}
		i++;
	}
}

static void	find_player_start(t_map *map)
{
	int		x;
	int		y;
	char	cell;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			cell = map->data[y][x];
			if (ft_strchr(RACIST_MAP_CHAR_PLAYER, cell))
			{
				map->player_start.x = x;
				map->player_start.y = y;
				map->player_start_dir = cell;
				return ;
			}
			x++;
		}
		y++;
	}
}

t_map	*map_from_str(const char *content, const char *map_path, int start)
{
	int		line_count;
	int		line_width;
	t_map	*map;

	line_count = count_lines(content);
	line_width = max_width(content);
	map = create_map(line_width, line_count);
	if (!map)
		return (NULL);
	map->map_path = map_path;
	map->start = start;
	copy_data(map, content);
	if (is_map_string_validinator(map) == false)
	{
		free_map(map);
		return (NULL);
	}
	find_player_start(map);
	return (map);
}
