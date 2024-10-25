/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:09:39 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/24 17:26:33 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	err_handl(void *p, char **map)
{
	if (p != NULL)
		free(p);
	if (map)
		free_map(map);
	get_next_line(-1);
	return (-1);
}

static char	*get_first_map_line(int fd, int skip_lines)
{
	char	*line;

	while (skip_lines > 0)
	{
		free(get_next_line(fd));
		skip_lines--;
	}
	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static int	get_width(char *line)
{
	int	len;

	len = 0;
	while (line && *line && *line != '\n')
	{
		if (*line != EMPTY && *line != WALL && *line != NORTH
			&& *line != SOUTH && *line != EAST && *line != WEST
			&& *line != SPACE && *line != DOOR && *line != ENEMY)
			return (-1);
		if ((*line == DOOR || *line == ENEMY) && !BONUS)
			return (-1);
		len++;
		line++;
	}
	return (len);
}

int	get_map_dimensions(t_map *map, int fd)
{
	char	*line;
	int		width;

	line = get_first_map_line(fd, 0);
	map->width = get_width(line);
	if (map->width <= 0)
		return (err_handl(line, NULL));
	map->height = 0;
	while (line)
	{
		width = get_width(line);
		if (width < 0)
			return (err_handl(line, NULL));
		if (width > map->width)
			map->width = width;
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	read_map_content(t_map *map, int fd, int start)
{
	int		i;
	int		len;

	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (-1);
	i = 0;
	map->grid[i] = ft_strdup2(get_first_map_line(fd, start), map->width + 1);
	while (i < map->height)
	{
		if (!map->grid[i])
			return (err_handl(NULL, map->grid));
		map->grid[i][map->width] = '\0';
		len = ft_strlen(map->grid[i]);
		if (map->grid[i][len - 1] == '\n')
			len--;
		ft_memset(map->grid[i] + len, ' ', map->width - len);
		i++;
		map->grid[i] = ft_strdup2(get_next_line(fd), map->width + 1);
	}
	get_next_line(-1);
	close(fd);
	return (0);
}
