/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:07:43 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/22 17:32:04 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	update_gun(t_player *player)
{
	long	ctime;

	ctime = currtime();
	if (ctime - player->gun_last_updated < 20)
		return (false);
	player->gun_last_updated = ctime;
	if (player->gun_texture == 2)
	{
		player->is_shooting = false;
		player->gun_texture = 0;
	}
	else
		player->gun_texture++;
	return (true);
}
