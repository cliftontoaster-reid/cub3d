/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_validotron.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:43:51 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/26 14:45:59 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map/table.h"
#include "utils/string.h"
#include <errno.h>

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
