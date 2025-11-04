/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:54:31 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 15:22:43 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils/panic.h"
#include <stdio.h>
#include <stdlib.h>

void	todo(const char *message, const char *file, int line)
{
	ft_putstr_fd("TODO: ", 2);
	if (message)
		ft_putstr_fd(message, 2);
	else
		ft_putstr_fd("No additional message provided.", 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Location: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(":", 2);
	perrornbr(line);
	ft_putstr_fd(".\n", 2);
	abort();
}
