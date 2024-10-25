/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:07:24 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/25 12:31:17 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	free_config(t_config *config)
{
	free(config->north);
	free(config->east);
	free(config->south);
	free(config->west);
	free(config->floor);
	free(config->ceiling);
	if (BONUS)
		free(config->door);
}

void	cleanup(t_data *data)
{
	if (data->map->grid != NULL)
		free_map(data->map->grid);
	if (data->map->doors != NULL)
		free(data->map->doors);
	if (data->enemies != NULL)
		free(data->enemies);
	if (data->mlx_ptr != NULL)
	{
		if (data->win_ptr != NULL)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->img_ptr != NULL)
			mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		unload_textures(data->mlx_ptr, data->textures);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}

void	clean_exit(t_data *data, char *message, int exit_status)
{
	cleanup(data);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	exit(exit_status);
}
