/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:24:58 by phartman          #+#    #+#             */
/*   Updated: 2024/10/23 18:15:34 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_enemy_texture(t_data *data)
{
	int		i;
	char	*index;
	char	filename[30];

	i = 0;
	while (i < 11)
	{
		ft_strlcpy(filename, "textures/sprite_", 17);
		index = ft_itoa(i);
		ft_strlcat(filename, index, 30);
		ft_strlcat(filename, ".xpm", 30);
		if (load_image(data->mlx_ptr, &data->textures->enemy[i], filename)
			== -1)
			return (-1);
		free(index);
		i++;
	}
	return (0);
}

static int	load_healthbar_texture(t_data *data)
{
	int		i;
	char	*index;
	char	filename[30];

	i = 0;
	while (i < 9)
	{
		ft_strlcpy(filename, "textures/healthbar_", 20);
		index = ft_itoa(i);
		ft_strlcat(filename, index, 30);
		ft_strlcat(filename, ".xpm", 30);
		if (load_image(data->mlx_ptr, &data->textures->healthbar[i],
				filename) == -1)
			return (-1);
		free(index);
		i++;
	}
	return (0);
}

static int	load_gun_textures(t_data *data)
{
	int		i;
	char	filename[18];

	i = 0;
	ft_strlcpy(filename, GUN_TEXTURE_BASE_NAME, 18);
	while (i < 3)
	{
		if (load_image(data->mlx_ptr, &data->textures->gun[i], filename) == -1)
			return (-1);
		filename[12]++;
		i++;
	}
	return (0);
}

static int	load_gameover_texture(t_data *data)
{
	if (load_image(data->mlx_ptr, &data->textures->gameover,
			"textures/game_over_screen.xpm") == -1)
		return (-1);
	return (0);
}

int	load_bonus_textures(t_data *data, t_config *cfg)
{
	if (load_image(data->mlx_ptr, &data->textures->door, cfg->door) == -1)
		return (-1);
	if (load_enemy_texture(data) == -1)
		return (-1);
	if (load_gun_textures(data) == -1)
		return (-1);
	if (load_healthbar_texture(data) == -1)
		return (-1);
	if (load_gameover_texture(data) == -1)
		return (-1);
	return (0);
}
