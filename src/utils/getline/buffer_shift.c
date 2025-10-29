/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_shift.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:12:52 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/29 16:29:29 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/getline.h"

void	buffer_shift(t_buffer *buffer, size_t shift)
{
	if (shift >= buffer->size)
	{
		buffer->size = 0;
		return ;
	}
	movemory(buffer->data, buffer->data + shift, buffer->size - shift);
	buffer->size -= shift;
}
