/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:53:31 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/03 15:52:07 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"
#include <stdlib.h>

void	*vec_pop_back(t_vec *vec)
{
	void	*elem;

	if (!vec || vec->size == 0)
		return (NULL);
	vec->size--;
	elem = (char *)vec->data + (vec->size * vec->elem_size);
	return (elem);
}
