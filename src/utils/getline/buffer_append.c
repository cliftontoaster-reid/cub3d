/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:44:56 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/29 16:28:50 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//
#include "utils/getline.h"

void	buffer_append(t_buffer *buffer, const char *data, size_t len)
{
	size_t	new_capacity;
	char	*new_data;

	if (buffer->size + len > buffer->capacity)
	{
		if (buffer->capacity == 0)
			new_capacity = 1;
		else
			new_capacity = buffer->capacity;
		while (new_capacity < buffer->size + len)
		{
			new_capacity *= 2;
		}
		new_data = (char *)malloc(new_capacity);
		if (buffer->data)
		{
			movemory(new_data, buffer->data, buffer->size);
			free(buffer->data);
		}
		buffer->data = new_data;
		buffer->capacity = new_capacity;
	}
	movemory(buffer->data + buffer->size, data, len);
	buffer->size += len;
}
