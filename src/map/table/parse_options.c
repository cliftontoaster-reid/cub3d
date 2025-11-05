/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:38:49 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/05 12:29:00 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map/table.h"
#include "utils/panic.h"
#include "utils/string.h"
#include <errno.h>
#include <stdlib.h>

static bool	isemptyline(const char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (*line != RACIST_MAP_CHAR_THE_DARK_EMPTY_VOID_OF_SPACE
			&& *line != '\t' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

static bool	isvalid_option(const char *id, int *idx)
{
	(*idx)++;
	if (ft_strcmp(id, "NO") == 0 && *idx == 1)
		return (true);
	if (ft_strcmp(id, "SO") == 0 && *idx == 2)
		return (true);
	if (ft_strcmp(id, "WE") == 0 && *idx == 3)
		return (true);
	if (ft_strcmp(id, "EA") == 0 && *idx == 4)
		return (true);
	if (ft_strcmp(id, "F") == 0 && *idx == 5)
		return (true);
	if (ft_strcmp(id, "C") == 0 && *idx == 6)
		return (true);
	return (false);
}

static bool	isvalid_value(const char *value)
{
	(void)value;
	return (true);
}

static bool	is_digit_str(const char *s)
{
	while (*s)
	{
		if (!(((*s >= '0' && *s <= '9') || *s == ',')))
			return (false);
		s++;
	}
	return (true);
}

static bool	is_valid_rgb_component(const char *s)
{
	int	fr;

	if (!is_digit_str(s))
		return (false);
	fr = ft_strfreq((char *)s, ',');
	if (fr != 2)
		return (false);
	return (true);
}

int	parse_rgb_value(const char *value)
{
	char	**limps;
	int		r;
	int		g;
	int		b;

	if (!is_valid_rgb_component(value))
	{
		errno = EINVAL;
		return (-1);
	}
	limps = ft_split(value, ',');
	if (!limps)
		return (-1);
	r = ft_atoi(limps[0]);
	g = ft_atoi(limps[1]);
	b = ft_atoi(limps[2]);
	free_string_array((const char **)limps, 3);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		errno = EINVAL;
		return (-1);
	}
	return ((r << 16) | (g << 8) | b);
}

static void	setoption(t_map *map, const char *option, const char *value)
{
	while (*value == RACIST_MAP_CHAR_THE_DARK_EMPTY_VOID_OF_SPACE
		|| *value == '\t')
		value++;
	if (ft_strcmp(option, "NO") == 0)
		map->north_wall_texture = ft_strdup(value);
	else if (ft_strcmp(option, "SO") == 0)
		map->south_wall_texture = ft_strdup(value);
	else if (ft_strcmp(option, "WE") == 0)
		map->west_wall_texture = ft_strdup(value);
	else if (ft_strcmp(option, "EA") == 0)
		map->east_wall_texture = ft_strdup(value);
	else if (ft_strcmp(option, "F") == 0)
		map->floor_color = parse_rgb_value(value);
	else if (ft_strcmp(option, "C") == 0)
		map->ceiling_color = parse_rgb_value(value);
}

bool	parse_options(t_map *map, const char **lines, int count)
{
	int		i;
	char	*parts[2];
	int		idx;

	idx = 0;
	i = 0;
	while (i < count)
	{
		if (!isemptyline(lines[i]))
		{
			if (!split_first(lines[i], ' ', parts))
				return (false);
			if (!isvalid_option(parts[0], &idx) || !isvalid_value(parts[1]))
			{
				free(parts[0]);
				return (false);
			}
			setoption(map, parts[0], parts[1]);
			free(parts[0]);
		}
		i++;
	}
	return (true);
}
