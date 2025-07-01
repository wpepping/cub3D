/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:26:41 by wpepping          #+#    #+#             */
/*   Updated: 2025/02/06 20:00:18 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_sprites(t_data *data, t_ray *rays);
static void	draw_env(t_ray *rays, t_data *data);

void	render_frame(t_data *data)
{
	t_ray	*rays;

	if (currtime() - data->last_render > MS_BETWEEN_FRAMES
		&& data->game_state == PLAYING)
	{
		rays = cast_rays(data->map, *data->player);
		if (rays == NULL)
			clean_exit(data, OOM_ERROR, 1);
		draw_env(rays, data);
		draw_minimap(data, rays);
		render_sprites(data, rays);
		data->last_render = currtime();
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0,
			0);
		if (BONUS)
			draw_bonus(data);
		free(rays);
	}
	if (data->game_state == GAME_OVER)
	{
		draw_gameover(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0,
			0);
	}
}

static void	draw_env(t_ray *rays, t_data *data)
{
	int		i;
	int		j;
	double	height;
	int		wall_top;

	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		height = projected_wall_height(data->focal_len, rays[i].dist);
		if (height > WINDOW_HEIGHT)
			wall_top = 0;
		else
			wall_top = WINDOW_HEIGHT / 2 - height / 2;
		j = 0;
		while (j < wall_top && j < WINDOW_HEIGHT)
			draw_ceiling(data, i, j++, data->textures->ceiling.img_ptr != NULL);
		while (j < wall_top + height && j < WINDOW_HEIGHT)
			draw_walls(data, rays, i, j++);
		while (j >= wall_top + height && j < WINDOW_HEIGHT)
			draw_floor(data, i, j++, data->textures->floor.img_ptr != NULL);
	}
}

static void	render_sprites(t_data *data, t_ray *rays)
{
	int			i;
	t_sprite	*sprite;
	t_sprite	enemy_sprite;

	i = 0;
	while (i < data->nr_of_enemies)
	{
		update_enemy_frame(&data->enemies[i]);
		enemy_sprite = ((t_sprite){data->enemies[i].pos, data->enemies[i].frame,
				data->enemies[i].size, data->enemies[i].size, true, false,
				NULL});
		sprite = get_sprite_coll(data, rays, &enemy_sprite);
		if (sprite != NULL)
			put_sprite(data, sprite);
		i++;
	}
}
