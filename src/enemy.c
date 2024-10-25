/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:13:35 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/24 15:39:13 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	enemy_hit_wall(t_coord pos, t_coord move, t_data *data)
{
	if (is_wall((t_coord){pos.x + move.x, pos.y}, data->map))
		return (true);
	if (is_wall((t_coord){pos.x, pos.y - move.y}, data->map))
		return (true);
	return (false);
}

static void	move_enemy(t_data *data, int i, double dir)
{
	t_coord	move;

	data->enemies[i].state = WALK;
	move.x = ENEMY_MOVE_SPEED / 2 * data->cos_table[angle_to_index(dir)];
	move.y = ENEMY_MOVE_SPEED / 2 * data->sin_table[angle_to_index(dir)];
	if (enemy_hit_wall(data->enemies[i].pos, (t_coord){move.x, 0}, data))
		move.x = 0;
	if (enemy_hit_wall(data->enemies[i].pos, (t_coord){0, move.y}, data))
		move.y = 0;
	data->enemies[i].pos.x += move.x;
	data->enemies[i].pos.y -= move.y;
}

int	move_enemies(t_data *data)
{
	double	dir;
	double	fire_dist;
	double	distance;
	int		i;
	bool	obstructed;

	i = 0;
	fire_dist = 200;
	obstructed = false;
	while (i < data->nr_of_enemies)
	{
		dir = get_dir_to(data->enemies[i].pos, data->player->pos);
		distance = get_dist(dir, data->enemies[i].pos, *data->player);
		obstructed = enemy_obstructed(data, i, distance);
		if (distance <= fire_dist && data->enemies[i].state != DIE
			&& !obstructed)
			attack(data, i);
		else if (data->enemies[i].state != DIE)
			move_enemy(data, i, dir);
		i++;
	}
	return (1);
}

void	kill_enemy(t_data *data, t_coord pos)
{
	int	i;

	i = 0;
	while (i < data->nr_of_enemies)
	{
		if ((int)(data->enemies[i].pos.x / CUBE_SIZE) == (int)pos.x
			&& (int)(data->enemies[i].pos.y / CUBE_SIZE) == (int)pos.y
			&& data->enemies[i].state != DIE)
		{
			data->enemies[i].state = DIE;
			return ;
		}
		i++;
	}
}

void	update_enemy_frame(t_enemy *enemy)
{
	double	current_time;

	current_time = currtime();
	if (current_time - enemy->last_frame_time >= MS_BETWEEN_FRAMES * 10)
	{
		if (enemy->state == ATTACK)
			enemy->frame = 0 + (enemy->frame + 1) % 4;
		else if (enemy->state == WALK)
			enemy->frame = 4 + (enemy->frame + 1 - 4) % 4;
		else if (enemy->state == DIE)
		{
			if (enemy->frame < 8)
				enemy->frame = 8;
			else if (enemy->frame >= 8 && enemy->frame < 10)
				enemy->frame++;
		}
		enemy->last_frame_time = current_time;
	}
}
