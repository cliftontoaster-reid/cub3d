/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:25:08 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/24 14:49:19 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "raycasting.h"
#include <unistd.h>

t_data	*get_texture(t_game *game, const char *path)
{
	t_data	*texture;

	texture = malloc(sizeof(t_data));
	if (!texture)
		return (NULL);
	texture->img = mlx_xpm_file_to_image(game->mlx, (char *)path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		free(texture);
		return (NULL);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_length, &texture->endian);
	return (texture);
}

void	free_texture(t_game *game, t_data *texture)
{
	if (texture)
	{
		if (texture->img)
			mlx_destroy_image(game->mlx, texture->img);
		free(texture);
	}
}

bool	load_textures(t_game *game, t_map *map)
{
	game->north = get_texture(game, map->north_wall_texture);
	if (!game->north)
		return (false);
	game->south = get_texture(game, map->south_wall_texture);
	if (!game->south)
	{
		free_texture(game, game->north);
		return (false);
	}
	game->east = get_texture(game, map->east_wall_texture);
	if (!game->east)
	{
		free_texture(game, game->north);
		free_texture(game, game->south);
		return (false);
	}
	game->west = get_texture(game, map->west_wall_texture);
	if (!game->west)
	{
		free_texture(game, game->north);
		free_texture(game, game->south);
		free_texture(game, game->east);
	}
	return (game->west != NULL);
}
