/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:53:07 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/03 15:52:22 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"

void	*vec_get(const t_vec *vec, size_t index)
{
	if (!vec || index >= vec->size)
		return (NULL);
	return ((char *)vec->data + (index * vec->elem_size));
}
