/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:49:38 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 13:58:33 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map/table.h"
#include "map/validatorinator.h"
#include "utils/reader.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	useful_perror(int errnum, const char *msg)
{
	errno = errnum;
	perror(msg);
}

static t_map	*read_da_map(const char *filename)
{
	char	*content;
	t_map	*map;

	content = read_file(filename);
	if (!content)
	{
		useful_perror(ENOMEM, "Error:\nCan't read map file ");
		return (NULL);
	}
	map = read_map(content);
	if (!map)
	{
		free(content);
		useful_perror(EINVAL, "Error:\nCan't parse map file ");
		return (NULL);
	}
	free(content);
	if (is_map_valid(map) == false)
	{
		free_map(map);
		useful_perror(EINVAL, "Error:\nMap is open ");
		return (NULL);
	}
	return (map);
}

void	print_map(t_map *map)
{
	int	i;

	if (!map)
	{
		printf("Map is NULL\n");
		return ;
	}
	printf("Map Width: %d, Height: %d\n", map->width, map->height);
	i = 0;
	while (i < map->height)
	{
		printf("%s\n", map->data[i]);
		i++;
	}
	printf("\nPlayer Start Position: (%d, %d) Direction: %c\n",
		map->player_start.x, map->player_start.y, map->player_start_dir);
	printf("North Wall Texture: %s\n", map->north_wall_texture);
	printf("South Wall Texture: %s\n", map->south_wall_texture);
	printf("West Wall Texture: %s\n", map->west_wall_texture);
	printf("East Wall Texture: %s\n", map->east_wall_texture);
	printf("Floor Color: %#06x\n", map->floor_color);
	printf("Ceiling Color: %#06x\n", map->ceiling_color);
}

int	main(int argc, char const *argv[])
{
	const char	*map_file = argv[1];
	size_t		len;
	t_map		*map;

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
	map = read_da_map(map_file);
	if (!map)
		return (1);
	print_map(map);
	free_map(map);
	return (0);
}
