/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:12:57 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/21 15:51:15 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_door	*get_door(t_map *map, t_coord coord)
{
	int	i;

	i = 0;
	while (i < map->nr_of_doors)
	{
		if (coord_equals(map->doors[i].coord, coord))
			return (&map->doors[i]);
		i++;
	}
	return (NULL);
}

bool	is_door(t_map *map, t_coord coord)
{
	t_coord	grid_coord;
	t_door	*door;

	grid_coord = pixel2grid(coord);
	if (map->grid[(int)grid_coord.y][(int)grid_coord.x] != DOOR)
		return (false);
	door = get_door(map, grid_coord);
	if (door->pos == 0 || (door->pos < 100 && door->state == CLOSING))
		return (true);
	return (false);
}

bool	is_door_coll(t_map *map, t_coord coll, bool is_horiz)
{
	t_coord	grid_coord;
	t_door	*door;
	int		door_coll;

	grid_coord = pixel2grid(coll);
	if (map->grid[(int)grid_coord.y][(int)grid_coord.x] != DOOR)
		return (false);
	door = get_door(map, grid_coord);
	if (is_horiz)
		door_coll = (int)coll.x % CUBE_SIZE * 100 / CUBE_SIZE;
	else
		door_coll = 100 - (int)coll.y % CUBE_SIZE * 100 / CUBE_SIZE;
	if (door_coll <= 5 || door_coll <= (100 - door->pos))
		return (true);
	return (false);
}

void	activate_door(t_data *data, t_coord c)
{
	t_door	*door;

	if (!data->active_door && data->map->grid[(int)c.y][(int)c.x] == DOOR)
	{
		door = get_door(data->map, c);
		if (door->pos == 0.0)
			door->state = OPENING;
		else
			door->state = CLOSING;
		door->last_move = currtime();
		data->active_door = door;
	}
}

bool	move_door(t_data *data, t_door *door)
{
	if (currtime() - door->last_move < 20)
		return (false);
	if (door->state == OPENING)
		door->pos += DOOR_STEP;
	else if (door->state == CLOSING)
		door->pos -= DOOR_STEP;
	door->last_move = currtime();
	if (door->pos == 0 || door->pos == 100)
	{
		door->state = IDLE;
		data->active_door = NULL;
	}
	return (true);
}
