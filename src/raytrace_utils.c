/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:26:24 by phartman          #+#    #+#             */
/*   Updated: 2024/10/22 13:32:22 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	projected_wall_height(int focal_len, double dist)
{
	return ((CUBE_SIZE / dist) * focal_len);
}

t_ray	update_ray(t_ray *r, double dist, bool is_horiz)
{
	r->dist = dist;
	r->is_horiz = is_horiz;
	return (*r);
}

t_coord	get_ray_delta_hori(t_ray *r)
{
	t_coord	delta;
	double	tan_val;

	tan_val = fabs(tan(r->dir));
	if (check_dir(r->dir, true) == SOUTH)
		delta.y = CUBE_SIZE;
	else
		delta.y = -CUBE_SIZE;
	if (tan_val == 0)
		delta.x = 0;
	else if (check_dir(r->dir, false) == WEST)
		delta.x = -CUBE_SIZE / tan_val;
	else
		delta.x = CUBE_SIZE / tan_val;
	return (delta);
}

t_coord	get_ray_delta_vert(t_ray *r)
{
	t_coord	delta;
	double	tan_val;

	tan_val = fabs(tan(r->dir));
	if (check_dir(r->dir, false) == EAST)
		delta.x = CUBE_SIZE;
	else
		delta.x = -CUBE_SIZE;
	if (tan_val == 0)
		delta.y = 0;
	else if (check_dir(r->dir, true) == NORTH)
		delta.y = -CUBE_SIZE * tan_val;
	else
		delta.y = CUBE_SIZE * tan_val;
	return (delta);
}

int	check_dir(double angle, bool is_horiz)
{
	if (is_horiz)
	{
		if (angle >= 0 && angle < M_PI)
			return (NORTH);
		else
			return (SOUTH);
	}
	else
	{
		if (angle >= M_PI / 2 && angle < 3 * M_PI / 2)
			return (WEST);
		else
			return (EAST);
	}
}
