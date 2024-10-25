/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:01:39 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/17 16:30:29 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord	pixel2grid(t_coord pixel_pos)
{
	t_coord	result;

	result.x = ((int)floor((pixel_pos.x / CUBE_SIZE)));
	result.y = ((int)floor((pixel_pos.y / CUBE_SIZE)));
	return (result);
}

int	get_map_item(t_coord pos, t_map *map)
{
	t_coord	grid_pos;

	grid_pos = pixel2grid(pos);
	if (grid_pos.x < 0 || grid_pos.x >= map->width
		|| grid_pos.y < 0 || grid_pos.y >= map->height)
		return (-1);
	return (map->grid[(int)grid_pos.y][(int)grid_pos.x]);
}

bool	coord_equals(t_coord c, t_coord d)
{
	return (c.x == d.x && c.y == d.y);
}

t_coord	coord_add(t_coord c, t_coord d)
{
	return ((t_coord){c.x + d.x, c.y + d.y});
}

int	get_dir(double angle)
{
	if (angle > 0.25 * M_PI && angle <= 0.75 * M_PI)
		return (NORTH);
	if (angle > 0.75 * M_PI && angle <= 1.25 * M_PI)
		return (WEST);
	if (angle > 1.25 * M_PI && angle <= 1.75 * M_PI)
		return (SOUTH);
	if (angle > 1.75 * M_PI || angle <= 0.25 * M_PI)
		return (EAST);
	return (-1);
}
