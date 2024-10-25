/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:15:24 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/25 12:37:34 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_door(t_map *map, int x, int y)
{
	int	west;
	int	east;
	int	north;
	int	south;

	west = map->grid[y][x - 1];
	east = map->grid[y][x + 1];
	north = map->grid[y - 1][x];
	south = map->grid[y + 1][x];
	if (x == 0 || x == map->width - 1 || y == 0 || y == map->height - 1)
		return (false);
	if (west == WALL && east == WALL && north != WALL && south != WALL
		&& north != DOOR && south != DOOR)
		return (true);
	if (north == WALL && south == WALL && west != WALL && east != WALL
		&& west != DOOR && east != DOOR)
		return (true);
	return (false);
}

static int	chk_tile(t_map *map, int x, int y, char **is_checked)
{
	int	result;

	if (is_checked[y][x] == 1)
		return (0);
	if (map->grid[y][x] == WALL)
		return (0);
	if (map->grid[y][x] == SPACE || x == 0 || x == map->width - 1 || y == 0
		|| y == map->height - 1)
		return (-1);
	if (map->grid[y][x] == DOOR && !is_valid_door(map, x, y))
		return (-1);
	result = 0;
	is_checked[y][x] = 1;
	return (result + chk_tile(map, x + 1, y, is_checked) + chk_tile(map, x - 1,
			y, is_checked) + chk_tile(map, x, y + 1, is_checked) + chk_tile(map,
			x, y - 1, is_checked));
}

int	is_valid_map(t_map *map, t_player *player)
{
	char	**is_checked;
	int		i;

	is_checked = ft_calloc(map->height + 1, sizeof(char *));
	i = 0;
	while (i < map->height)
		is_checked[i++] = ft_calloc(map->width, sizeof(char));
	i = chk_tile(map, player->pos.x / CUBE_SIZE, player->pos.y / CUBE_SIZE,
			is_checked);
	free_map(is_checked);
	if (i)
		return (0);
	return (1);
}
