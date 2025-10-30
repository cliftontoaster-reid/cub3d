/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:51:19 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 14:54:26 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
//
#include "utils/panic.h"

static void	printnbr(int n)
{
	char	result[12];
	int		i;

	i = 0;
	while (n >= 0)
	{
		result[i++] = (n % 10) + '0';
		n /= 10;
		if (n == 0)
			break ;
	}
	result[i] = '\0';
	perror(result);
}

void	panic(const char *message, const char *file, int line)
{
	perror("An error (");
	perror(message);
	perror(") occurred at file: ");
	perror(file);
	perror(" on line: ");
	printnbr(line);
	perror(".\n");
	abort();
}
