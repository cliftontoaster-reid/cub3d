/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:45:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 11:18:47 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils/alloc.h"
#include "utils/string.h"
#include <stdlib.h>
#include <sys/types.h>

bool	split_first(const char *s, char delimiter, char **out)
{
	const char	*delimiter_pos;
	size_t		pos;

	if (!s || !out)
		return (false);
	delimiter_pos = ft_strchr(s, delimiter);
	if (!delimiter_pos)
		return (false);
	pos = delimiter_pos - s;
	out[0] = ft_strndup(s, pos);
	if (!out[0])
		return (false);
	out[1] = (char *)delimiter_pos + 1;
	return (true);
}
