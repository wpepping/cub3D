/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:14:07 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/23 19:14:10 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->key_state = (t_key_state){0, 0, 0, 0, 0, 0, 0};
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img_ptr = NULL;
	data->active_door = NULL;
	data->enemies = NULL;
	data->last_render = currtime();
	data->last_move_time = currtime();
	data->last_strafe_time = currtime();
	data->mouse_x = WINDOW_WIDTH / 2;
	data->focal_len = (WINDOW_WIDTH / 2.0) / (tan(FOV / 2.0));
	data->game_state = PLAYING;
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->doors = NULL;
}

void	init_config(t_config *config)
{
	config->floor = NULL;
	config->ceiling = NULL;
	config->door = NULL;
	config->enemy = NULL;
	config->north = NULL;
	config->east = NULL;
	config->south = NULL;
	config->west = NULL;
	config->map_start = 0;
}

int	init_window(t_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_NAME);
	if (data->win_ptr == NULL)
		return (-1);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->img_ptr == NULL)
		return (-1);
	data->imgbuff = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&(data->lsize), &(data->endian));
	return (0);
}

void	init_events(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_key_press, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask,
		&handle_key_release, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask,
		&handle_close, data);
	mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask,
		&handle_mouse_move, data);
	mlx_hook(data->win_ptr, ButtonPress, ButtonPressMask,
		&handle_mouse_click, data);
	mlx_loop_hook(data->mlx_ptr, &handle_loop, data);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr,
		WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
}
