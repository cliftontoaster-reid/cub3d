/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_with_marker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:13:10 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/10 16:07:45 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/panic.h"
#include <stdio.h>

void	print_header(const char *msg, t_floodfillinator *ffi, int row, int col)
{
	printf(ANSI_RED "%s" ANSI_RESET "\n   --> ", msg);
	printf(ANSI_ITA ANSI_UNDER "%s:%d:%d\n" ANSI_RESET, ffi->map_path, row + 1
		+ ffi->start, col + 1);
}

void	print_row(int j, t_floodfillinator *ffi)
{
	int	i;

	printf("%2d | ", j);
	i = 0;
	while (i < ffi->width)
	{
		if ((ffi->visited[j][i] && ffi->map[j][i] == '0')
			|| ffi->map[j][i] == 'N')
			printf("%s%c%s", ANSI_GREEN, ffi->map[j][i], ANSI_RESET);
		else if (ffi->map[j][i] == '1')
			printf("%s%c%s", ANSI_PINK, ffi->map[j][i], ANSI_RESET);
		else
			printf("%s%c%s", ANSI_YELLOW, ffi->map[j][i], ANSI_RESET);
		i++;
	}
	printf("\n");
}

void	print_marker(int col)
{
	int	i;

	for (i = -4; i <= col; i++)
		printf(" ");
	printf(ANSI_RED "^%s\n", ANSI_RESET);
}

void	print_map_with_marker(int row, int col, t_floodfillinator *ffi,
		const char *msg)
{
	int	j;

	printf("Error:\n");
	print_header(msg, ffi, row, col);
	j = 0;
	while (j < ffi->height)
	{
		print_row(j, ffi);
		if (j == row)
			print_marker(col);
		j++;
	}
}

void	print_map_with_marker_simple(int row, int col, t_map *map,
		const char *msg)
{
	int	j;
	int	i;

	printf("Error:\n");
	printf(ANSI_RED "%s" ANSI_RESET "\n   --> ", msg);
	if (row == -1 && col == -1)
		printf(ANSI_ITA ANSI_UNDER "%s\n" ANSI_RESET, map->map_path);
	else
		printf(ANSI_ITA ANSI_UNDER "%s:%d:%d\n" ANSI_RESET, map->map_path, row
			+ 1 + map->start, col + 1);
	j = 0;
	while (j < map->height)
	{
		printf("%2d | ", j);
		i = 0;
		while (i < map->width)
		{
			printf("%c", map->data[j][i]);
			i++;
		}
		printf("\n");
		if (j == row)
			print_marker(col);
		j++;
	}
}
