/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:12:35 by phartman          #+#    #+#             */
/*   Updated: 2024/10/24 20:55:19 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	heal(t_data *data);

void	set_game_state(t_data *data)
{
	if (data->player->health == 0)
		data->game_state = GAME_OVER;
	heal(data);
}

static void	heal(t_data *data)
{
	int				i;
	bool			being_attacked;
	static double	last_healed;
	double			current_time;

	current_time = currtime();
	being_attacked = false;
	i = -1;
	while (++i < data->nr_of_enemies)
	{
		if (data->enemies[i].state == ATTACK)
		{
			being_attacked = true;
			break ;
		}
	}
	if (current_time - last_healed >= 5000 && !being_attacked)
	{
		if (data->player->health < 9)
			data->player->health++;
		last_healed = current_time;
	}
}

void	attack(t_data *data, int i)
{
	double			current_time;
	static double	last_attacked;

	data->enemies[i].state = ATTACK;
	current_time = currtime();
	if (current_time - last_attacked >= 2000)
	{
		if (data->player->health > 0)
			data->player->health--;
		last_attacked = current_time;
	}
}

bool	enemy_obstructed(t_data *data, int i, double distance)
{
	t_ray	*ray;
	double	horiz_coll;
	double	vert_coll;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		cleanup(data);
	ray->dir = get_dir_to(data->enemies[i].pos, data->player->pos);
	ray->coll = data->enemies[i].pos;
	horiz_coll = get_horiz_coll(*data->player, ray, data->map);
	vert_coll = get_vert_coll(*data->player, ray, data->map);
	free(ray);
	if (horiz_coll < vert_coll)
		return (horiz_coll <= distance);
	else
		return (vert_coll <= distance);
	return (false);
}

void	draw_gameover(t_data *data)
{
	t_coord	img_start;
	int		i;
	int		j;
	t_coord	size;

	size.x = data->textures->gameover.width;
	size.y = data->textures->gameover.height;
	img_start.x = (WINDOW_WIDTH / 2) - (size.x / 2);
	img_start.y = (WINDOW_HEIGHT / 2) - (size.y / 2);
	i = 0;
	j = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			put_pixel_from_img(data, &data->textures->gameover, (t_coord){j, i},
				(t_coord){img_start.x + j, img_start.y + i});
			j++;
		}
		i++;
	}
}
