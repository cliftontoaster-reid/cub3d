/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_to_cstring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:15:59 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 15:00:02 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//
#include "utils/alloc.h"

char	*buffer_to_cstring(const t_buffer *buffer)
{
	char	*cstring;

	cstring = (char *)malloc(buffer->size + 1);
	if (!cstring)
		return (NULL);
	movemory(cstring, buffer->data, buffer->size);
	cstring[buffer->size] = '\0';
	return (cstring);
}
