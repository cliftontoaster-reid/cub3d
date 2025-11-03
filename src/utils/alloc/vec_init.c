/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:53:23 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/03 15:52:11 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"
#include <stdlib.h>

void	vec_init(t_vec *vec, size_t elem_size)
{
	if (!vec)
		return ;
	vec->data = NULL;
	vec->size = 0;
	vec->capacity = 0;
	vec->elem_size = elem_size;
}
