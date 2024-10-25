/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:19:31 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/24 15:40:01 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	should_move(bool direction, bool opposite)
{
	if (!direction || opposite)
		return (false);
	return (true);
}

static double	speed_multiplier(bool run, bool diagonal)
{
	double	move_speed;

	move_speed = 1;
	if (run)
		move_speed *= 2;
	if (diagonal)
		move_speed /= SQRT_2;
	return (move_speed);
}

bool	move_player(t_data *data, bool rev)
{
	t_coord		move;
	double		move_speed;
	t_player	*player;

	player = data->player;
	move_speed = 1.0 * MOVE_SPEED * speed_multiplier(data->key_state.run,
			data->key_state.mv_l || data->key_state.mv_r);
	if (rev)
		move_speed *= -1;
	move.x = move_speed * data->cos_table[angle_to_index(data->player->dir)];
	move.y = move_speed * data->sin_table[angle_to_index(data->player->dir)];
	if (is_wall((t_coord){player->pos.x + move.x, player->pos.y}, data->map))
		move.x = 0;
	if (is_wall((t_coord){player->pos.x, player->pos.y - move.y}, data->map))
		move.y = 0;
	player->pos.x += move.x;
	player->pos.y -= move.y;
	return (true);
}

bool	strafe_player(t_data *data, bool left)
{
	t_coord		move;
	double		move_speed;
	double		strafe_dir;
	t_player	*player;

	player = data->player;
	move_speed = 1.0 * MOVE_SPEED * speed_multiplier(data->key_state.run,
			data->key_state.mv_up || data->key_state.mv_dn);
	move_speed = MOVE_SPEED;
	if (left)
		strafe_dir = norm_angle(data->player->dir + M_PI / 2);
	else
		strafe_dir = norm_angle(data->player->dir - M_PI / 2);
	move.x = move_speed * data->cos_table[angle_to_index(strafe_dir)];
	move.y = move_speed * data->sin_table[angle_to_index(strafe_dir)];
	if (is_wall((t_coord){player->pos.x + move.x, player->pos.y}, data->map))
		move.x = 0;
	if (is_wall((t_coord){player->pos.x, player->pos.y - move.y}, data->map))
		move.y = 0;
	data->player->pos.x += move.x;
	data->player->pos.y -= move.y;
	return (true);
}

bool	rotate_player(t_data *data, bool left, double rotate_speed)
{
	if (left)
		rotate_speed *= -1;
	data->player->dir -= rotate_speed;
	data->player->dir = norm_angle(data->player->dir);
	return (true);
}
