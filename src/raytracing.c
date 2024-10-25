/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:36:33 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/24 20:57:02 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_coord	get_wall_coll(t_coord coll, t_ray *r, t_map *map,
					bool is_horiz);
static t_ray	init_ray(double dir, int i);

t_ray	*cast_rays(t_map *map, t_player p)
{
	int		i;
	t_ray	*rays;
	t_ray	ray[2];
	double	horiz_coll;
	double	vert_coll;

	i = 0;
	rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);
	if (!rays)
		return (NULL);
	while (i < WINDOW_WIDTH)
	{
		ray[0] = init_ray(p.dir, i);
		ray[1] = init_ray(p.dir, i);
		horiz_coll = get_horiz_coll(p, &ray[0], map);
		vert_coll = get_vert_coll(p, &ray[1], map);
		if (horiz_coll < vert_coll)
			rays[i] = update_ray(&ray[0], horiz_coll, true);
		else
			rays[i] = update_ray(&ray[1], vert_coll, false);
		i++;
	}
	return (rays);
}

double	get_vert_coll(t_player p, t_ray *r, t_map *map)
{
	t_coord	coll;
	double	tan_val;
	double	dist;

	tan_val = fabs(tan(r->dir));
	if (check_dir(r->dir, false) == WEST)
		coll.x = floor(p.pos.x / CUBE_SIZE) * CUBE_SIZE - 1;
	else
		coll.x = floor(p.pos.x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	if (check_dir(r->dir, true) == NORTH)
		coll.y = p.pos.y - fabs(p.pos.x - coll.x) * tan_val;
	else
		coll.y = p.pos.y + fabs(p.pos.x - coll.x) * tan_val;
	r->coll = get_wall_coll(coll, r, map, false);
	dist = get_dist(r->dir, r->coll, p);
	return (dist);
}

double	get_horiz_coll(t_player p, t_ray *r, t_map *map)
{
	t_coord	coll;
	double	tan_val;

	tan_val = fabs(tan(r->dir));
	if (tan_val == 0)
		return (INFINITY);
	if (check_dir(r->dir, true) == NORTH)
		coll.y = floor(p.pos.y / CUBE_SIZE) * CUBE_SIZE - 1;
	else
		coll.y = floor(p.pos.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	if (check_dir(r->dir, false) == WEST)
		coll.x = p.pos.x - fabs(p.pos.y - coll.y) / tan_val;
	else
		coll.x = p.pos.x + fabs(p.pos.y - coll.y) / tan_val;
	r->coll = get_wall_coll(coll, r, map, true);
	return (get_dist(r->dir, r->coll, p));
}

static t_coord	get_wall_coll(t_coord coll, t_ray *r, t_map *map, bool is_horiz)
{
	t_coord	delta;
	int		map_x;
	int		map_y;

	map_x = ((int)floor((coll.x / CUBE_SIZE)));
	map_y = ((int)floor((coll.y / CUBE_SIZE)));
	if (is_horiz)
		delta = get_ray_delta_hori(r);
	else
		delta = get_ray_delta_vert(r);
	while (!(map_x < 0 || map_y < 0 || map_x > map->width - 1
			|| map_y > map->height - 1))
	{
		r->map_item = get_map_item(coll, map);
		r->is_door = (r->map_item == DOOR && is_door_coll(map, coll, is_horiz));
		if (r->is_door || r->map_item == WALL)
			return (coll);
		coll.x += delta.x;
		coll.y += delta.y;
		map_x = ((int)floor((coll.x / CUBE_SIZE)));
		map_y = ((int)floor((coll.y / CUBE_SIZE)));
	}
	return ((t_coord){-1.0, -1.0});
}

static t_ray	init_ray(double dir, int i)
{
	t_ray	r;

	r.dir = dir + (FOV / 2) - (FOV / WINDOW_WIDTH) * i;
	r.dir = norm_angle(r.dir);
	r.is_horiz = false;
	return (r);
}
