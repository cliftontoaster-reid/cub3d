/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:53:23 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 13:48:24 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"
#include <stdlib.h>

t_vec	*vec_init(size_t elem_size)
{
	t_vec	*vec;

	vec = (t_vec *)malloc(sizeof(t_vec));
	if (!vec)
		return (NULL);
	vec->data = NULL;
	vec->size = 0;
	vec->capacity = 0;
	vec->elem_size = elem_size;
	return (vec);
}
