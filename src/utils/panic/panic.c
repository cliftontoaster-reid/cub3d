/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:51:19 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 16:57:34 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
//
#include "utils/panic.h"

void	panic(const char *message, const char *file, int line)
{
	perror("An error (");
	perror(message);
	perror(") occurred at : ");
	perror(file);
	perror(":");
	perrornbr(line);
	perror(".\n");
	abort();
}
