/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:46:14 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 13:10:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//
#include "utils/alloc.h"

void	buffer_free(t_buffer *buffer)
{
	if (buffer->data)
	{
		free(buffer->data);
		buffer->data = NULL;
	}
	buffer->size = 0;
	buffer->capacity = 0;
}
