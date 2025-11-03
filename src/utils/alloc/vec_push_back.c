/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:54:40 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/03 13:55:57 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"
#include <stdlib.h>

static bool	expand_capacity(t_vec *vec)
{
	size_t	new_capacity;
	void	*new_data;

	if (vec->capacity == 0)
		new_capacity = 1;
	else
		new_capacity = vec->capacity;
	while (new_capacity < vec->size + 1)
		new_capacity *= 2;
	new_data = malloc(new_capacity * vec->elem_size);
	if (!new_data)
		return (false);
	if (vec->data)
	{
		movemory(new_data, vec->data, vec->size * vec->elem_size);
		free(vec->data);
	}
	vec->data = new_data;
	vec->capacity = new_capacity;
	return (true);
}

bool	vec_push_back(t_vec *vec, const void *elem)
{
	void	*dest;

	if (!vec || !elem)
		return (false);
	if (vec->size >= vec->capacity)
	{
		if (!expand_capacity(vec))
			return (false);
	}
	dest = (char *)vec->data + (vec->size * vec->elem_size);
	movemory(dest, elem, vec->elem_size);
	vec->size++;
	return (true);
}
