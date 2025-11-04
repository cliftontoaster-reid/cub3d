/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:48:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/04 13:48:34 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

typedef struct s_buffer
{
	char	*data;
	size_t	size;
	size_t	capacity;
}			t_buffer;

void		buffer_init(t_buffer *buffer);
void		buffer_append(t_buffer *buffer, const char *data, size_t len);
void		buffer_shift(t_buffer *buffer, size_t shift);
void		buffer_free(t_buffer *buffer);
ssize_t		buffer_is_line(const t_buffer *buffer);
char		*buffer_to_cstring(const t_buffer *buffer);
void		movemory(void *dest, const void *src, size_t n);

typedef struct s_vec
{
	void	*data;
	size_t	size;
	size_t	capacity;
	size_t	elem_size;
}			t_vec;

t_vec		*vec_init(size_t elem_size);
bool		vec_push_back(t_vec *vec, const void *elem);
bool		vec_push_back_absent(t_vec *vec, const void *elem);
bool		vec_expand_capacity(t_vec *vec, size_t min_capacity);
void		*vec_get(const t_vec *vec, size_t index);
void		*vec_pop_back(t_vec *vec);
void		vec_free(t_vec *vec);
