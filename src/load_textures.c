/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:14:28 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/24 17:27:13 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_image(void *mlx_ptr, t_image *img, char *fname)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, fname, &img->width,
			&img->height);
	if (img->img_ptr == NULL)
		return (-1);
	img->buff = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->lsize,
			&img->endian);
	return (0);
}

int	load_textures(t_data *data, t_config *cfg)
{
	bool	xpm;

	if (load_image(data->mlx_ptr, &data->textures->north, cfg->north) == -1
		|| load_image(data->mlx_ptr, &data->textures->east, cfg->east) == -1
		|| load_image(data->mlx_ptr, &data->textures->south, cfg->south) == -1
		|| load_image(data->mlx_ptr, &data->textures->west, cfg->west) == -1)
		return (-1);
	xpm = BONUS && !ft_strncmp(file_ext(cfg->floor), ".xpm", 4);
	if (xpm && load_image(data->mlx_ptr, &data->textures->floor, cfg->floor)
		== -1)
		return (-1);
	else if (!xpm && save_rgbs(cfg->floor, data->floor) == -1)
		return (-1);
	xpm = BONUS && !ft_strncmp(file_ext(cfg->ceiling), ".xpm", 4);
	if (xpm && load_image(data->mlx_ptr, &data->textures->ceiling,
			cfg->ceiling) == -1)
		return (-1);
	else if (!xpm && save_rgbs(cfg->ceiling, data->ceiling) == -1)
		return (-1);
	if (BONUS && load_bonus_textures(data, cfg) == -1)
		return (-1);
	return (0);
}
