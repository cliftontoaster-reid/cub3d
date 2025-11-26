/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:13:39 by zamohame          #+#    #+#             */
/*   Updated: 2025/11/26 14:17:11 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include <math.h>

static char	get_tile(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return ('1');
	return (map->data[y][x]);
}

static void	init_ray_steps(t_ray_ctx *ctx, t_player *player, t_vec2d ray)
{
	ctx->upos.x = (int)player->x;
	ctx->upos.y = (int)player->y;
	ctx->delta.x = fabs(1.0 / ray.x);
	ctx->delta.y = fabs(1.0 / ray.y);
	ctx->step.x = -1 + 2 * (ray.x >= 0);
	ctx->step.y = -1 + 2 * (ray.y >= 0);
	if (ray.x < 0)
		ctx->side.x = (player->x - ctx->upos.x) * ctx->delta.x;
	else
		ctx->side.x = (ctx->upos.x + 1.0 - player->x) * ctx->delta.x;
	if (ray.y < 0)
		ctx->side.y = (player->y - ctx->upos.y) * ctx->delta.y;
	else
		ctx->side.y = (ctx->upos.y + 1.0 - player->y) * ctx->delta.y;
}

static void	dda_loop(t_ray_ctx *ctx, t_map *map)
{
	while (1)
	{
		if (ctx->side.x < ctx->side.y)
		{
			ctx->side.x += ctx->delta.x;
			ctx->upos.x += ctx->step.x;
			ctx->hit_vertical = 1;
		}
		else
		{
			ctx->side.y += ctx->delta.y;
			ctx->upos.y += ctx->step.y;
			ctx->hit_vertical = 0;
		}
		if (get_tile(map, ctx->upos.x, ctx->upos.y) == '1')
			break ;
	}
}

static t_rayhit	compute_hit(t_ray_ctx *ctx, t_player *player, t_vec2d ray)
{
	t_rayhit	hit;

	hit.map_x = ctx->upos.x;
	hit.map_y = ctx->upos.y;
	if (ctx->hit_vertical)
	{
		hit.side = 2 + (ctx->step.x != 1);
		hit.perp_dist = (ctx->upos.x - player->x + (1 - ctx->step.x) / 2)
			/ ray.x;
		hit.hit_x = player->y + hit.perp_dist * ray.y;
	}
	else
	{
		hit.side = (ctx->step.y != 1);
		hit.perp_dist = (ctx->upos.y - player->y + (1 - ctx->step.y) / 2)
			/ ray.y;
		hit.hit_x = player->x + hit.perp_dist * ray.x;
	}
	hit.hit_x = hit.hit_x - floor(hit.hit_x);
	return (hit);
}

void	cast_all_rays(t_game *game, t_player *player, t_map *map, t_data *data)
{
	int			col;
	t_rayhit	hit;
	double		camera_x;
	t_vec2d		ray;
	t_ray_ctx	ctx;

	col = 0;
	while (col < WINDOW_WIDTH)
	{
		camera_x = 2.0 * (double)col / (double)WINDOW_WIDTH - 1.0;
		ray.x = player->dir_x + player->plane_x * camera_x;
		ray.y = player->dir_y + player->plane_y * camera_x;
		init_ray_steps(&ctx, player, ray);
		dda_loop(&ctx, map);
		hit = compute_hit(&ctx, player, ray);
		draw_wall(game, data, col, hit);
		col++;
	}
}
