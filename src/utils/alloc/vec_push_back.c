/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:54:40 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/03 15:51:51 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"
#include <stdlib.h>

bool	vec_push_back(t_vec *vec, const void *elem)
{
	void	*dest;

	if (!vec || !elem)
		return (false);
	if (vec->size >= vec->capacity)
	{
		if (!vec_expand_capacity(vec, vec->size + 1))
			return (false);
	}
	dest = (char *)vec->data + (vec->size * vec->elem_size);
	movemory(dest, elem, vec->elem_size);
	vec->size++;
	return (true);
}
