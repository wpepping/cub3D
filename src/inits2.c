/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:14:16 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/24 15:34:48 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_textures *textures)
{
	int	i;

	i = 0;
	while (i < 11)
		textures->enemy[i++].img_ptr = NULL;
	i = 0;
	while (i < 3)
		textures->gun[i++].img_ptr = NULL;
	i = 0;
	while (i < 9)
		textures->healthbar[i++].img_ptr = NULL;
	textures->north.img_ptr = NULL;
	textures->east.img_ptr = NULL;
	textures->south.img_ptr = NULL;
	textures->west.img_ptr = NULL;
	textures->floor.img_ptr = NULL;
	textures->ceiling.img_ptr = NULL;
	textures->door.img_ptr = NULL;
	textures->gameover.img_ptr = NULL;
}

void	init_trig_tables(double *sin_table, double *cos_table)
{
	double	angle;
	int		i;

	i = 0;
	while (i < 3600)
	{
		angle = deg_to_rad(i * 0.1);
		sin_table[i] = sin(angle);
		cos_table[i] = cos(angle);
		i++;
	}
}

int	init_doors(t_map *map)
{
	int	i;
	int	j;
	int	n;

	map->nr_of_doors = nr_of_thing(map, DOOR);
	if (map->nr_of_doors != 0)
	{
		map->doors = malloc(map->nr_of_doors * sizeof(t_door));
		if (map->doors == NULL)
			return (-1);
	}
	n = 0;
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
			if (map->grid[j++][i] == DOOR)
				map->doors[n++] = (t_door){(t_coord){i, j - 1}, IDLE, 0, 0};
		i++;
	}
	return (0);
}

void	init_enemy(t_data *data, int i, int j, int n)
{
	data->enemies[n].size = 128;
	data->enemies[n].pos = (t_coord){i * CUBE_SIZE, j * CUBE_SIZE};
	data->enemies[n].target = data->player->pos;
	data->enemies[n].state = WALK;
	data->enemies[n].frame = 4;
	data->enemies[n++].last_frame_time = currtime();
}

int	init_enemies(t_data *data)
{
	int	i;
	int	j;
	int	n;

	data->enemies = NULL;
	data->nr_of_enemies = nr_of_thing(data->map, ENEMY);
	if (data->nr_of_enemies != 0)
	{
		data->enemies = malloc(data->nr_of_enemies * sizeof(t_enemy));
		if (data->enemies == NULL)
			return (-1);
	}
	n = 0;
	i = -1;
	while (++i < data->map->width)
	{
		j = -1;
		while (++j < data->map->height)
			if (data->map->grid[j][i] == ENEMY && n < data->nr_of_enemies)
				init_enemy(data, i, j, n++);
	}
	return (0);
}
