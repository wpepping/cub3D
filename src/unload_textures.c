/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unload_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:25:26 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/23 18:14:37 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	unload_bonus_textures(void *mlx_ptr, t_textures *textures)
{
	int	i;

	i = 0;
	if (textures->gameover.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->gameover.img_ptr);
	while (i < 11)
	{
		if (i < 3 && textures->gun[i].img_ptr)
			mlx_destroy_image(mlx_ptr, textures->gun[i].img_ptr);
		if (i < 9 && textures->healthbar[i].img_ptr)
			mlx_destroy_image(mlx_ptr, textures->healthbar[i].img_ptr);
		if (textures->enemy[i].img_ptr)
			mlx_destroy_image(mlx_ptr, textures->enemy[i].img_ptr);
		i++;
	}
}

void	unload_textures(void *mlx_ptr, t_textures *textures)
{
	if (textures->north.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->north.img_ptr);
	if (textures->east.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->east.img_ptr);
	if (textures->south.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->south.img_ptr);
	if (textures->west.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->west.img_ptr);
	if (textures->floor.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->floor.img_ptr);
	if (textures->ceiling.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->ceiling.img_ptr);
	if (textures->door.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->door.img_ptr);
	if (BONUS)
		unload_bonus_textures(mlx_ptr, textures);
}
