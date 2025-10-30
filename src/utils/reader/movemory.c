/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movemory.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:28:32 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 16:48:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/reader.h"

/// @brief Copies n bytes from memory area src to memory area dest.
/// @warning The memory areas must not overlap.
/// @param dest Pointer to the destination memory area.
/// @param src Pointer to the source memory area.
/// @param n Number of bytes to copy.
void	movemory(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else if (d > s)
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
}
