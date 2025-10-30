/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:38:49 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 17:01:25 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/table.h"
#include "utils/panic.h"
#include "utils/string.h"
#include <stdlib.h>
#include <string.h>

// TODO: remove string.h

static bool	isemptyline(const char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

static int	strlenght(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static bool	isvalid_option(const char *id)
{
	int	len;

	len = strlenght(id);
	if (len < 1 || len > 3)
		return (false);
	else if (len == 1)
	{
		if (id[0] == 'F' || id[0] == 'C')
			return (false);
	}
	else if (len == 2)
	{
		if ((id[0] == 'N' && id[1] == 'O') || (id[0] == 'S' && id[1] == 'O')
			|| (id[0] == 'W' && id[1] == 'E') || (id[0] == 'E' && id[1] == 'A'))
			return (true);
	}
	return (false);
}

static bool	isvalid_value(const char *value)
{
	(void)value;
	return (true);
}

static void	setoption(t_map *map, const char *option, const char *value)
{
	if (strcmp(option, "NO") == 0)
		map->north_wall_texture = strdup(value);
	else if (strcmp(option, "SO") == 0)
		map->south_wall_texture = strdup(value);
	else if (strcmp(option, "WE") == 0)
		map->west_wall_texture = strdup(value);
	else if (strcmp(option, "EA") == 0)
		map->east_wall_texture = strdup(value);
	else if (strcmp(option, "F") == 0)
		todo("Parse RGB value", __FILE__, __LINE__);
	else if (strcmp(option, "C") == 0)
		todo("Parse RGB value", __FILE__, __LINE__);
}

bool	parse_options(t_map *map, const char **lines, int count)
{
	int		i;
	char	*parts[2];

	i = 0;
	while (i < count)
	{
		if (!isemptyline(lines[i]) && split_first(lines[i], ' ', parts))
		{
			if (!isvalid_option(parts[0]))
				return (false);
			if (!isvalid_value(parts[1]))
				return (false);
			setoption(map, parts[0], parts[1]);
			free(parts[0]);
		}
		i++;
	}
	return (true);
}
