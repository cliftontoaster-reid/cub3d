/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/31 11:19:53 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"
#include "utils/string.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	movemory(dup, s, len);
	dup[len] = '\0';
	return (dup);
}
