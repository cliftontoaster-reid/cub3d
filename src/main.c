/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:49:38 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/10 16:46:05 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map/table.h"
#include "map/validatorinator.h"
#include "mlx.h"
#include "raycasting.h"
#include "utils/panic.h"
#include "utils/reader.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef VERSION
# define VERSION "something went wrong"
#endif

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
	map = read_map(content, filename);
	if (!map)
	{
		free(content);
		return (NULL);
	}
	free(content);
	if (is_map_valid(map, filename) == false)
	{
		free_map(map);
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

void	print_legal(void)
{
	printf("Copyright (c) 2025, Clifton Toaster Reid & zamohame\n");
	printf("This software is provided under the BSD-3-Clause License.\n");
	printf("A copy of the license can be found in the LICENSE file.\n");
	printf("If you did not receive a copy, see");
	printf(" https://opensource.org/licenses/BSD-3-Clause\n\n");
}

static int	start_game(t_map *map)
{
	void		*mlx;
	void		*win;
	t_data		data;
	t_player	player;

	mlx = mlx_init();
	win = mlx_new_window(mlx, win_width, win_height, "Cub3D v" VERSION);
	data.img = mlx_new_image(mlx, win_width, win_height);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
			&data.endian);
	printf("Initializing player...\n");
	init_player(&player, map);
	cast_all_rays(&player, map, &data);
	// draw_minimap(&img, map, &player);
	mlx_put_image_to_window(mlx, win, data.img, 0, 0);
	// mlx_hook(win, 2, 1L << 0, handle_keypress, &data);
	printf("Entering main loop...\n");
	mlx_loop(mlx);
	return (0);
}

int	main(int argc, char const *argv[])
{
	const char	*map_file = argv[1];
	size_t		len;
	t_map		*map;

	print_legal();
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
	start_game(map);
	print_map(map);
	free_map(map);
	return (0);
}
