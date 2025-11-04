/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 11:26:07 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils/alloc.h"
#include "utils/string.h"
#include <stdlib.h>

static int	count_lines(const char *s)
{
	int	count;

	count = 0;
	if (!s || *s == '\0')
		return (0);
	while (*s)
	{
		if (*s == '\n')
			count++;
		s++;
	}
	if (s[-1] != '\n')
		count++;
	return (count);
}

static char	*allocate_and_copy_line(const char *start, const char *end,
		const char **arr, int i)
{
	char	*line;

	line = ft_strndup(start, end - start);
	if (!line)
	{
		while (i > 0)
			free((void *)arr[--i]);
		free(arr);
		return (NULL);
	}
	return (line);
}

static const char	**allocate_string_array(int count)
{
	const char	**arr;

	arr = (const char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	return (arr);
}

static const char	**fill_array(const char **arr, const char *s, int count)
{
	int			i;
	const char	*start;
	const char	*end;

	i = 0;
	start = s;
	while (i < count)
	{
		end = ft_strchr(start, '\n');
		if (!end)
			end = start + ft_strlen(start);
		arr[i] = allocate_and_copy_line(start, end, arr, i);
		if (!arr[i])
			return (NULL);
		start = end + 1;
		i++;
	}
	arr[count] = NULL;
	return (arr);
}

const char	**split_lines(const char *s, int *out_count)
{
	const char	**arr;
	int			count;

	count = count_lines(s);
	if (count == 0)
	{
		if (out_count)
			*out_count = 0;
		return (NULL);
	}
	if (out_count)
		*out_count = count;
	arr = allocate_string_array(count);
	if (!arr)
		return (NULL);
	return (fill_array(arr, s, count));
}
