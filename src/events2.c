/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:14:01 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/23 19:14:02 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse_click(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == Button1)
		kill_enemy(data, get_gridpos_in_front(data->player));
	if (!data->player->is_shooting)
	{
		data->player->is_shooting = true;
		data->player->gun_last_updated = currtime();
	}
	return (0);
}
