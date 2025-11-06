/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_perror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:51:57 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/06 15:52:14 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/panic.h"
#include <errno.h>
#include <stdio.h>

void	useful_perror(int errnum, const char *msg)
{
	errno = errnum;
	perror(msg);
}
