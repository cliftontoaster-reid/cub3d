/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:37:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/29 16:29:02 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>
#include <sys/types.h>

typedef struct s_buffer
{
	char	*data;
	size_t	size;
	size_t	capacity;
}			t_buffer;

#define READ_SIZE 1024

ssize_t		get_next_line(int fd, char **line);

void		buffer_init(t_buffer *buffer);
void		buffer_append(t_buffer *buffer, const char *data, size_t len);
void		buffer_shift(t_buffer *buffer, size_t shift);
void		buffer_free(t_buffer *buffer);
ssize_t		buffer_is_line(const t_buffer *buffer);
void		movemory(void *dest, const void *src, size_t n);