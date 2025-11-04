/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:49:38 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 11:56:08 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils/reader.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char const *argv[])
{
	const char	*map_file = argv[1];
	size_t		len;

	if (argc != 2)
	{
		printf("Usage: %s <map file>\n", argv[0]);
		exit(1);
	}
	len = ft_strlen(map_file);
	if (len < 5 || ft_strcmp(map_file + len - 4, ".cub") != 0)
	{
		printf("Error: Map file must have .cub extension\n");
		exit(1);
	}
	printf("Starting game with map file: %s\n", map_file);
	return (0);
}
