/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:58:17 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/24 16:18:37 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord	get_gridpos_in_front(t_player *player)
{
	int	player_dir;

	player_dir = get_dir(player->dir);
	if (player_dir == NORTH)
		return (coord_add(pixel2grid(player->pos), (t_coord){0, -1}));
	if (player_dir == EAST)
		return (coord_add(pixel2grid(player->pos), (t_coord){1, 0}));
	if (player_dir == SOUTH)
		return (coord_add(pixel2grid(player->pos), (t_coord){0, 1}));
	if (player_dir == WEST)
		return (coord_add(pixel2grid(player->pos), (t_coord){-1, 0}));
	return ((t_coord){-1, -1});
}

int	max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

double	get_dir_to(t_coord pos, t_coord target)
{
	return (norm_angle(-atan2(target.y - pos.y, target.x - pos.x)));
}

int	init_line_vars(t_coord p1, t_coord p2, t_coord *dist, t_coord *step)
{
	int	err;

	dist->x = abs((int)p2.x - (int)p1.x);
	dist->y = abs((int)p2.y - (int)p1.y);
	err = dist->x - dist->y;
	if (p1.x < p2.x)
		step->x = 1;
	else
		step->x = -1;
	if (p1.y < p2.y)
		step->y = 1;
	else
		step->y = -1;
	return (err);
}

t_coord	get_offset(t_data *data)
{
	int	player_tile_x;
	int	player_tile_y;
	int	offset_x;
	int	offset_y;

	player_tile_x = (data->player->pos.x / CUBE_SIZE) * TILE_SZ;
	player_tile_y = (data->player->pos.y / CUBE_SIZE) * TILE_SZ;
	offset_x = max(player_tile_x - MINI_SIZE / 2, 0);
	offset_y = max(player_tile_y - MINI_SIZE / 2, 0);
	return ((t_coord){offset_x, offset_y});
}
