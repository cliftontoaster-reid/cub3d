/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:44:31 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 13:10:43 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"

void	buffer_init(t_buffer *buffer)
{
	buffer->data = NULL;
	buffer->size = 0;
	buffer->capacity = 0;
}
