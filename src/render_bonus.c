/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:30:08 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/25 12:32:34 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_healthbar(t_data *data)
{
	int	img_start_x;
	int	img_start_y;
	int	i;
	int	j;
	int	health;

	health = data->player->health;
	img_start_x = WINDOW_WIDTH - data->textures->healthbar[health - 1].width;
	img_start_y = 10;
	i = 0;
	j = 0;
	while (i < data->textures->healthbar[health - 1].width)
	{
		j = 0;
		while (j < data->textures->healthbar[health - 1].height)
		{
			put_pixel_from_img(data, &data->textures->healthbar[health - 1],
				(t_coord){j, i}, (t_coord){img_start_x + j, img_start_y + i});
			j++;
		}
		i++;
	}
}

static void	draw_gun(t_data *data)
{
	t_coord	img_start;
	t_coord	size;
	int		i;
	int		j;

	size.x = data->textures->gun[data->player->gun_texture].width;
	size.y = data->textures->gun[data->player->gun_texture].height;
	img_start.x = (WINDOW_WIDTH - size.x) / 2;
	img_start.y = WINDOW_HEIGHT - size.y;
	i = 0;
	j = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			put_pixel_from_img(data,
				&data->textures->gun[data->player->gun_texture], (t_coord){j,
				i}, (t_coord){img_start.x + j, img_start.y + i});
			j++;
		}
		i++;
	}
}

void	draw_bonus(t_data *data)
{
	draw_healthbar(data);
	draw_gun(data);
}
