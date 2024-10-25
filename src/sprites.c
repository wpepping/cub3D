/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:14:23 by phartman          #+#    #+#             */
/*   Updated: 2024/10/24 20:54:52 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_sprite_info(t_data *data, t_hit *info_arr, t_sprite *sprite,
				int len);
static bool	hit_sprite(t_ray *r, t_data *data, double scale, t_sprite *sprite);
static int	calculate_sprite_parameters(t_data *data, t_sprite *sprite,
				double *scale, int *screen_y);

void	put_sprite(t_data *data, t_sprite *sprite)
{
	int		i;
	int		j;
	double	scale;
	int		screen_y;
	int		offset;

	offset = calculate_sprite_parameters(data, sprite, &scale, &screen_y);
	i = -1;
	while (++i < (int)(sprite->width * scale) && i < sprite->info->len)
	{
		j = -1;
		while (++j < (int)(sprite->height * scale) && j < WINDOW_HEIGHT
			- screen_y)
		{
			if ((int)(i / scale) >= 0 && i / scale < sprite->width && (int)(j
					/ scale) >= 0 && (int)(j / scale) < sprite->height)
				put_pixel_from_img(data, &data->textures->enemy[sprite->frame],
					(t_coord){(int)((i + offset) / scale), (int)(j / scale)},
					(t_coord){sprite->info->min_x + i, screen_y + j});
		}
	}
	free(sprite->info);
}

t_sprite	*get_sprite_coll(t_data *data, t_ray *rays, t_sprite *sprite)
{
	int		i;
	double	dist;
	t_hit	info_arr[WINDOW_WIDTH];
	int		info_len;

	i = -1;
	dist = get_dist(get_dir_to(data->player->pos, sprite->pos), sprite->pos,
			*data->player);
	info_len = 0;
	ft_bzero(info_arr, sizeof(t_hit) * WINDOW_WIDTH);
	while (++i < WINDOW_WIDTH)
		if (hit_sprite(&rays[i], data, data->focal_len / dist, sprite)
			&& rays[i].dist > dist)
			info_arr[info_len++] = (t_hit){rays[i].dir, i};
	if (info_len > 0)
	{
		set_sprite_info(data, info_arr, sprite, info_len);
		return (sprite);
	}
	return (NULL);
}

static void	set_sprite_info(t_data *data, t_hit *info_arr, t_sprite *sprite,
		int len)
{
	int				i;
	double			middle;
	int				closest;
	double			dir_to_sprite;
	t_sprite_info	*info;

	i = 0;
	middle = 10000;
	info = malloc(sizeof(t_sprite_info));
	if(!info)
		cleanup(data);
	dir_to_sprite = get_dir_to(data->player->pos, sprite->pos);
	info->min_x = info_arr[i].screen_x;
	while (i < len)
	{
		if (fabs(info_arr[i].dir - dir_to_sprite) < middle)
		{
			middle = fabs(info_arr[i].dir - dir_to_sprite);
			closest = i;
		}
		i++;
	}
	info->len = i;
	info->dir = dir_to_sprite;
	info->middle = closest;
	info->max_x = info->min_x + info->len;
	sprite->info = info;
}

static bool	hit_sprite(t_ray *r, t_data *data, double scale, t_sprite *sprite)
{
	int		scaled_width;
	double	dir_to_sprite;
	double	left_angle;
	double	right_angle;
	double	screen_width;

	scaled_width = (int)(sprite->width * scale);
	screen_width = scaled_width * FOV / WINDOW_WIDTH;
	dir_to_sprite = get_dir_to(data->player->pos, sprite->pos);
	left_angle = norm_angle(dir_to_sprite - (screen_width / 2.0));
	right_angle = norm_angle(dir_to_sprite + (screen_width / 2.0));
	if ((r->dir >= left_angle && r->dir <= right_angle)
		|| (left_angle > right_angle && (r->dir >= left_angle
				|| r->dir <= right_angle)))
		return (true);
	return (false);
}

static int	calculate_sprite_parameters(t_data *data, t_sprite *sprite,
		double *scale, int *screen_y)
{
	double	dist;
	double	dir_to_sprite;
	int		width;
	int		offset;

	dir_to_sprite = get_dir_to(data->player->pos, sprite->pos);
	dist = get_dist(dir_to_sprite, sprite->pos, *data->player);
	*scale = data->focal_len / dist;
	width = (int)(sprite->width * (*scale));
	*screen_y = WINDOW_HEIGHT / 2 - (int)(sprite->pos.y / dist);
	offset = 0;
	if (sprite->info->middle <= sprite->info->len / 2
		&& sprite->info->len < width)
		offset = width - sprite->info->len;
	return (offset);
}
