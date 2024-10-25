/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:13:16 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/24 16:05:16 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	err_handl(char *error_msg, t_data *data)
{
	ft_putendl_fd(error_msg, 2);
	cleanup(data);
	return (-1);
}

static int	init(t_data *data, char *fname)
{
	init_data(data);
	init_map(data->map);
	init_trig_tables(data->sin_table, data->cos_table);
	init_textures(data->textures);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (err_handl(OOM_ERROR, data));
	if (read_map(data, fname) < 0)
		return (err_handl(MAP_ERROR, data));
	if (init_doors(data->map) < 0)
		return (err_handl(OOM_ERROR, data));
	if (init_enemies(data) < 0)
		return (err_handl(OOM_ERROR, data));
	if (init_window(data) < 0)
		return (err_handl(OOM_ERROR, data));
	return (0);
}

static int	check_input(int argc, char **argv)
{
	if (argc != 2 || ft_strncmp(file_ext(argv[1]), ".cub", 5) != 0)
	{
		ft_putendl_fd("Usage: cub3d <map name>.cub", 2);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_map		map;
	t_player	player;
	t_textures	textures;

	data.map = &map;
	player.health = 9;
	data.player = &player;
	data.textures = &textures;
	if (check_input(argc, argv) < 0 || init(&data, argv[1]) < 0)
		return (1);
	if (init_player(&map, &player) < 0 || !is_valid_map(&map, &player))
	{
		ft_putendl_fd(MAP_ERROR, STDERR_FILENO);
		cleanup(&data);
		return (1);
	}
	init_events(&data);
	render_frame(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_loop(data.mlx_ptr);
	cleanup(&data);
	return (0);
}
