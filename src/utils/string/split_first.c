/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:45:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 16:57:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"
#include "utils/string.h"
#include <stdlib.h>
#include <sys/types.h>

static size_t	sizelen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

bool	split_first(const char *s, char delimiter, char **out)
{
	size_t	pos;
	size_t	i;
	size_t	len;

	if (!s || !out)
		return (false);
	len = sizelen(s);
	i = 0;
	while (i < len)
	{
		if (s[i] == delimiter)
			break ;
		i++;
	}
	if (i == len)
		return (false);
	pos = i;
	out[0] = malloc(sizeof(char) * (pos + 1));
	if (!out[0])
		return (false);
	movemory(out[0], s, pos);
	out[0][pos] = '\0';
	if (pos < len)
		out[1] = (char *)&s[pos + 1];
	else
	{
		free(out[0]);
		out[0] = NULL;
		return (false);
	}
	return (true);
}
