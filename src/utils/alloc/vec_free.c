/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:52:28 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/03 13:52:59 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/alloc.h"
#include <stdlib.h>

void	vec_free(t_vec *vec)
{
	if (!vec)
		return ;
	if (vec->data)
		free(vec->data);
	free(vec);
}
