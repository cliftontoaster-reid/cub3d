/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:44:56 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/26 14:12:33 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"
#include <stdlib.h>

static void	buffer_resize(t_buffer *buffer, size_t min_capacity)
{
	size_t	new_capacity;
	char	*new_data;

	if (min_capacity <= buffer->capacity)
		return ;
	if (buffer->capacity == 0)
	{
		new_capacity = 1;
	}
	else
	{
		new_capacity = buffer->capacity;
	}
	while (new_capacity < min_capacity)
		new_capacity *= 2;
	new_data = (char *)malloc(new_capacity);
	if (!new_data)
		return ;
	if (buffer->data)
	{
		movemory(new_data, buffer->data, buffer->size);
		free(buffer->data);
	}
	buffer->data = new_data;
	buffer->capacity = new_capacity;
}

void	buffer_append(t_buffer *buffer, const char *data, size_t len)
{
	buffer_resize(buffer, buffer->size + len);
	movemory(buffer->data + buffer->size, data, len);
	buffer->size += len;
}
