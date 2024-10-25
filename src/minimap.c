/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:32:47 by phartman          #+#    #+#             */
/*   Updated: 2024/10/24 16:59:02 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_data *data, t_coord pos, int size, int c[3]);
static void	draw_line(t_data *data, t_coord p1, t_coord p2);
static void	draw_player(t_data *data, t_ray *rays, t_coord offset);
static void	draw_enemies(t_data *data, t_coord offset);

void	draw_minimap(t_data *data, t_ray *rays)
{
	int		y;
	int		x;
	t_coord	offset;
	t_coord	pos;

	offset = get_offset(data);
	y = offset.y;
	while (y / TILE_SZ < data->map->height && y < MINI_SIZE + offset.y)
	{
		x = offset.x;
		while (x / TILE_SZ < data->map->width && x < MINI_SIZE + offset.x)
		{
			pos = (t_coord){x - offset.x, y - offset.y};
			if (data->map->grid[y / TILE_SZ][x / TILE_SZ] == WALL)
				draw_square(data, pos, TILE_SZ / 10, (int [3]){95, 95, 95});
			else if (data->map->grid[y / TILE_SZ][x / TILE_SZ] == DOOR)
				draw_square(data, pos, TILE_SZ / 10, (int [3]){0, 0, 255});
			else if (data->map->grid[y / TILE_SZ][x / TILE_SZ] != SPACE)
				draw_square(data, pos, TILE_SZ / 10, (int [3]){195, 195, 195});
			x += TILE_SZ / 10;
		}
		y += TILE_SZ / 10;
	}
	draw_player(data, rays, offset);
	draw_enemies(data, offset);
}

static void	draw_square(t_data *data, t_coord pos, int size, int c[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			set_pixel(data, c, pos.x + i, pos.y + j);
			j++;
		}
		i++;
	}
}

static void	draw_line(t_data *data, t_coord p1, t_coord p2)
{
	t_coord	dist;
	t_coord	step;
	int		err;

	err = init_line_vars(p1, p2, &dist, &step);
	while (p1.x < data->map->width * TILE_SZ && p1.y < data->map->height
		* TILE_SZ && p1.x >= 0 && p1.y >= 0)
	{
		set_pixel(data, (int [3]){255, 255, 255}, (int)p1.x, (int)p1.y);
		if (fabs(p1.x - p2.x) < 2 && fabs(p1.y - p2.y) < 2)
			break ;
		if (2 * err > -dist.y)
		{
			p1.x += step.x;
			err -= dist.y;
		}
		if (2 * err < dist.x)
		{
			p1.y += step.y;
			err += dist.x;
		}
	}
}

static void	draw_player(t_data *data, t_ray *rays, t_coord offset)
{
	t_coord	p;
	t_coord	end_line;
	int		i;

	i = 0;
	p.x = data->player->pos.x / CUBE_SIZE * TILE_SZ - offset.x;
	p.y = data->player->pos.y / CUBE_SIZE * TILE_SZ - offset.y;
	draw_square(data, (t_coord){p.x - 2.5, p.y - 2.5}, 5, (int [3]){0, 255, 0});
	while (i < WINDOW_WIDTH)
	{
		if (i % 20 == 0 && i != 0)
		{
			end_line.x = rays[i].coll.x / CUBE_SIZE * TILE_SZ - offset.x;
			end_line.y = rays[i].coll.y / CUBE_SIZE * TILE_SZ - offset.y;
			if (end_line.x > MINI_SIZE)
				end_line.x = MINI_SIZE + TILE_SZ;
			if (end_line.y > MINI_SIZE)
				end_line.y = MINI_SIZE + TILE_SZ;
			draw_line(data, p, end_line);
		}
		i++;
	}
}

static void	draw_enemies(t_data *data, t_coord offset)
{
	int		i;
	t_coord	e;

	i = 0;
	while (i < data->nr_of_enemies)
	{
		if (data->enemies[i].state != DIE)
		{
			e.x = data->enemies[i].pos.x / CUBE_SIZE * TILE_SZ - offset.x;
			e.y = data->enemies[i].pos.y / CUBE_SIZE * TILE_SZ - offset.y;
			if (e.x >= 0 && e.y >= 0 && e.x < MINI_SIZE && e.y < MINI_SIZE)
				draw_square(data, (t_coord){e.x, e.y}, 5, (int [3]){255, 0, 0});
		}
		i++;
	}
}
