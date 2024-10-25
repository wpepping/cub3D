/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:14:48 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/22 18:07:49 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_player(t_map *map, t_player *player)
{
	t_coord	coord;
	int		n;
	char	c;

	coord.y = 0;
	n = -1;
	while (coord.y < map->height)
	{
		coord.x = 0;
		while (coord.x < map->width)
		{
			c = map->grid[(int)coord.y][(int)coord.x];
			if (c == NORTH || c == EAST || c == SOUTH || c == WEST)
			{
				if (n++ > -1)
					return (-1);
				player->pos.x = coord.x * CUBE_SIZE + 0.5 * CUBE_SIZE;
				player->pos.y = coord.y * CUBE_SIZE + 0.5 * CUBE_SIZE;
				player->dir = get_angle(c);
			}
			coord.x++;
		}
		coord.y++;
	}
	return (n);
}

int	init_player(t_map *map, t_player *player)
{
	player->gun_texture = 0;
	player->is_shooting = false;
	player->gun_last_updated = currtime();
	return (find_player(map, player));
}
