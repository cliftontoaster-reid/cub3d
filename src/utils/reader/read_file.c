/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:53:12 by lfiorell          #+#    #+#             */
/*   Updated: 2025/10/30 13:19:59 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
//
#include "utils/alloc.h"
#include "utils/reader.h"

/// @brief Reads the entire content of a file specified by its path.
/// @param path The path to the file to read.
/// @return A pointer to the file content, or NULL on failure.
char	*read_file(const char *path)
{
	t_buffer	buffer;
	char		*content;
	char		cbuffer[READ_SIZE];
	int			fd;
	ssize_t		bytes_read;

	buffer_init(&buffer);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	bytes_read = read(fd, cbuffer, READ_SIZE);
	while (bytes_read > 0)
	{
		buffer_append(&buffer, cbuffer, bytes_read);
		bytes_read = read(fd, cbuffer, READ_SIZE);
	}
	close(fd);
	content = buffer_to_cstring(&buffer);
	buffer_free(&buffer);
	return (content);
}
