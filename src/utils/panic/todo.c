/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:54:31 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 17:00:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/panic.h"
#include <stdio.h>
#include <stdlib.h>

void	todo(const char *message, const char *file, int line)
{
	perror("TODO: ");
	if (message)
		perror(message);
	else
		perror("No additional message provided.");
	perror("\n");
	perror("Location: ");
	perror(file);
	perror(":");
	perrornbr(line);
	perror(".\n");
	abort();
}
