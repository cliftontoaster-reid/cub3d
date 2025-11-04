/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push_back_absent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:04:12 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 15:31:14 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils/alloc.h"
#include <stdlib.h>

static bool	is_inside(const t_vec *vec, const void *elem)
{
	size_t	i;
	char	*vec_data;
	char	*elem_data;

	vec_data = (char *)vec->data;
	elem_data = (char *)elem;
	i = 0;
	while (i < vec->size)
	{
		if (ft_memcmp(vec_data + (i * vec->elem_size), elem_data,
				vec->elem_size) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	vec_push_back_absent(t_vec *vec, const void *elem)
{
	if (!vec || !elem)
		return (false);
	if (is_inside(vec, elem))
		return (true);
	return (vec_push_back(vec, elem));
}
