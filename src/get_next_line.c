/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:00:49 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/27 20:20:56 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	alloc_strs(char **res, char **rstbff, char **readbff, int *strbff)
{
	int	i;
	int	memsize;
	int	zero;

	zero = 0;
	if (*rstbff == NULL)
	{
		*rstbff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (*rstbff == NULL)
			return (0);
		(*rstbff)[0] = '\0';
	}
	*strbff = 64;
	memsize = *strbff * sizeof(char);
	*res = malloc(memsize);
	if (*res == NULL)
		return (*(int *)free_and_return(&zero, NULL, NULL, rstbff));
	*readbff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (*readbff == NULL)
		return (*(int *)free_and_return(&zero, *res, NULL, rstbff));
	i = 0;
	while (i < memsize)
		(*res)[i++] = '\0';
	return (1);
}

void	copy_restbuff(char *src, char *dest, int start)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (src[i] != '\0')
		dest[j++] = src[i++];
	dest[j] = '\0';
}

static int	process_restbuff(char *restbuff, char **result, int *strbuff)
{
	int		i;
	int		res_nr;

	i = 0;
	res_nr = 1;
	while (restbuff[i] != '\0' && restbuff[i] != '\n')
		i++;
	if (restbuff[i] == '\0')
		i -= res_nr--;
	*result = strecat(*result, restbuff, i + 1, strbuff);
	if (result == NULL)
		return (-1);
	copy_restbuff(restbuff, restbuff, i + 1);
	return (res_nr);
}

int	read_from_file(char *readbuff, char **result, int *strbuff, int fd)
{
	int		bytes_read;
	char	*eoln_p;
	int		len;

	bytes_read = read(fd, readbuff, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (-2);
	readbuff[bytes_read] = '\0';
	while (bytes_read > 0)
	{
		len = bytes_read;
		eoln_p = gnl_strchr(readbuff, '\n');
		if (eoln_p != NULL)
			len = eoln_p - readbuff + 1;
		*result = strecat(*result, readbuff, len, strbuff);
		if (*result == NULL)
			return (-2);
		if (eoln_p != NULL)
			return (len - 1);
		bytes_read = read(fd, readbuff, BUFFER_SIZE);
		readbuff[bytes_read] = '\0';
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*restbuff;
	char		*readbuff;
	char		*result;
	int			strbuff;
	int			temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return ((char *)free_and_return(NULL, NULL, NULL, &restbuff));
	if (!alloc_strs(&result, &restbuff, &readbuff, &strbuff))
		return (NULL);
	temp = process_restbuff(restbuff, &result, &strbuff);
	if (temp == -1)
		return ((char *)free_and_return(NULL, readbuff, NULL, NULL));
	if (temp == 1)
		return ((char *)free_and_return(result, readbuff, NULL, NULL));
	temp = read_from_file(readbuff, &result, &strbuff, fd);
	if (temp == -2 && restbuff[0] == '\0' && result && result[0] == '\0')
		return ((char *)free_and_return(NULL, readbuff, result, &restbuff));
	if (temp == -2 && restbuff[0] == '\0')
		return ((char *)free_and_return(result, readbuff, NULL, &restbuff));
	if (temp > -1)
		copy_restbuff(readbuff, restbuff, temp + 1);
	return ((char *)free_and_return(result, readbuff, NULL, NULL));
}
