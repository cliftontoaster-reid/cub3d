/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:47:52 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 15:19:22 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
//
#include "utils/alloc.h"
#include "utils/reader.h"

static inline ssize_t	get_size(const t_buffer *buffer, ssize_t newline_pos)
{
	if (newline_pos >= 0)
		return (newline_pos);
	return (buffer->size);
}

static ssize_t	read_until_newline(int fd, t_buffer *buffer)
{
	char	temp[READ_SIZE];
	ssize_t	bytes_read;
	ssize_t	newline_pos;

	bytes_read = read(fd, temp, READ_SIZE);
	while (bytes_read > 0)
	{
		buffer_append(buffer, temp, bytes_read);
		newline_pos = buffer_is_line(buffer);
		if (newline_pos >= 0)
			return (newline_pos);
		bytes_read = read(fd, temp, READ_SIZE);
	}
	if (bytes_read < 0)
		return (-1);
	if (bytes_read > 0)
		return ((ssize_t)buffer->size);
	return (-1);
}

static char	*extract_line(t_buffer *buffer, ssize_t newline_pos)
{
	char	*result_line;
	ssize_t	size;

	size = get_size(buffer, newline_pos);
	result_line = (char *)malloc(size + 1);
	if (!result_line)
		return (NULL);
	movemory(result_line, buffer->data, size);
	result_line[size] = '\0';
	return (result_line);
}

ssize_t	get_next_line(int fd, char **line)
{
	static t_buffer	buffer;
	static int		cfd = -1;
	ssize_t			newline_pos;

	if (fd < 0 || !line)
		return (-1);
	if (cfd != fd)
	{
		buffer_free(&buffer);
		buffer_init(&buffer);
		cfd = fd;
	}
	newline_pos = read_until_newline(fd, &buffer);
	if (newline_pos < 0)
		return (buffer_free(&buffer), -1);
	*line = extract_line(&buffer, newline_pos);
	if (!*line)
		return (buffer_free(&buffer), -1);
	buffer_shift(&buffer, newline_pos + 1);
	return (1);
}
