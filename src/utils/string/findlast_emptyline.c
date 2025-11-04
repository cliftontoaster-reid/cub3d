/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findlast_emptyline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:52:13 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 11:27:45 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map/validatorinator.h"
#include "utils/string.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

static bool	iswhite(char c)
{
	return (c == RACIST_MAP_CHAR_THE_DARK_EMPTY_VOID_OF_SPACE || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*findlast_emptyline(const char *s)
{
	size_t	len;
	ssize_t	i;
	ssize_t	j;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len < 2)
		return (NULL);
	i = len - 1;
	while (i > 0)
	{
		if (s[i] == '\n')
		{
			j = i - 1;
			while (j >= 0 && iswhite(s[j]) && s[j] != '\n')
				j--;
			if (j >= 0 && s[j] == '\n')
				return ((char *)&s[j]);
		}
		i--;
	}
	return (NULL);
}
