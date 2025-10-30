/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perrornbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:56:40 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 16:56:50 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/panic.h"
#include <stdio.h>

void	perrornbr(int n)
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
