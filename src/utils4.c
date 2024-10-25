/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:18 by phartman          #+#    #+#             */
/*   Updated: 2024/10/24 15:37:56 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	nr_of_thing(t_map *map, int thing)
{
	int	i;
	int	j;
	int	result;

	result = 0;
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
			if (map->grid[j++][i] == thing)
				result++;
		i++;
	}
	return (result);
}

int	angle_to_index(double angle)
{
	double	n_angle;
	int		index;

	n_angle = norm_angle(angle);
	index = (int)(n_angle * 3600 / (2 * M_PI));
	return (index % 3600);
}

bool	is_wall(t_coord pos, t_map *map)
{
	char	map_item;
	bool	isdoor;

	map_item = get_map_item(pos, map);
	isdoor = (map_item == DOOR && is_door(map, pos));
	if (isdoor || map_item == WALL)
		return (true);
	return (false);
}
