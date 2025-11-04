/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_is_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:25:36 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 13:10:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"

ssize_t	buffer_is_line(const t_buffer *buffer)
{
	ssize_t	i;

	i = 0;
	while (i < (ssize_t)buffer->size)
	{
		if (buffer->data[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
