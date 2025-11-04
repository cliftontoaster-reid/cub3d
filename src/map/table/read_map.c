/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:59:28 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 11:20:07 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map/table.h"
#include "utils/string.h"
#include <stdlib.h>

static bool	makeparse(t_map *map, char *options_part)
{
	const char	**lines;
	int			count;
	bool		result;

	lines = split_lines(options_part, &count);
	free(options_part);
	if (lines == NULL)
		return (false);
	result = parse_options(map, lines, count);
	free_string_array(lines, count);
	return (result);
}

static void	freeifneeded(t_map *map, char *options_part, char *map_part)
{
	if (options_part)
		free(options_part);
	if (map_part)
		free(map_part);
	if (map)
		free_map(map);
}

t_map	*read_map(const char *fullcontent)
{
	char	*last_line;
	char	*map_part;
	char	*options_part;
	t_map	*map;

	last_line = findlast_emptyline(fullcontent);
	if (last_line == NULL)
		return (NULL);
	options_part = ft_strndup(fullcontent, last_line - fullcontent);
	map_part = ft_strdup(last_line + 1);
	if (options_part == NULL || map_part == NULL)
	{
		freeifneeded(NULL, options_part, map_part);
		return (NULL);
	}
	map = map_from_str(map_part);
	if (map == NULL || !makeparse(map, options_part))
	{
		free_map(map);
		free(map_part);
		return (NULL);
	}
	free(map_part);
	return (map);
}
