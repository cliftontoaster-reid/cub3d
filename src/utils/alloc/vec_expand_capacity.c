/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_expand_capacity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:01:09 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 15:15:57 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"
#include <stdlib.h>

bool	vec_expand_capacity(t_vec *vec, size_t min_capacity)
{
	size_t	new_capacity;
	void	*new_data;

	if (!vec)
		return (false);
	new_capacity = vec->capacity * 2;
	if (new_capacity < 1)
		new_capacity = 1;
	while (new_capacity < min_capacity || new_capacity < vec->size)
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
