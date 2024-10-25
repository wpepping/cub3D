/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:54:58 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/22 14:46:06 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_isnum(char *str)
{
	while (*str)
		if (!ft_isdigit(*(str++)))
			return (false);
	return (true);
}

double	get_angle(char dir)
{
	if (dir == NORTH)
		return (0.5 * M_PI);
	if (dir == EAST)
		return (0);
	if (dir == SOUTH)
		return (1.5 * M_PI);
	else
		return (M_PI);
}

char	*file_ext(char *fname)
{
	int		strlen;
	int		i;

	strlen = ft_strlen(fname);
	i = fmax(strlen - 5, 0);
	while (fname[i] != '.' && fname[i] != '\0')
		i++;
	return (fname + i);
}

long	currtime(void)
{
	struct timeval	result;

	if (gettimeofday(&result, NULL))
		ft_putendl_fd("Error getting current time.", STDOUT_FILENO);
	return (result.tv_sec * 1000 + result.tv_usec / 1000);
}

char	*ft_strdup2(char *s, size_t n)
{
	int		i;
	char	*dup;

	if (s == NULL)
		return (NULL);
	i = 0;
	dup = malloc(n +1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	free(s);
	return (dup);
}
