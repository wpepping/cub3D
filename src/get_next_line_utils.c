/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:31:33 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/27 20:20:49 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*strecat(char *dest, char *src, int len, int *strbuff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i += 1;
	while (j < len && src[j] != '\0')
	{
		if (i + j + 2 > *strbuff)
		{
			dest = extstr(dest, strbuff);
			if (dest == NULL)
				return (NULL);
		}
		dest[i + j] = (src)[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*extstr(char *src, int *buffer)
{
	char	*result;
	int		i;
	int		memsize;

	*buffer *= 2;
	memsize = *buffer * sizeof(char);
	result = malloc(memsize);
	if (result != NULL)
	{
		i = 0;
		while (src[i] != '\0')
		{
			result[i] = src[i];
			i++;
		}
		while (i < memsize)
			result[i++] = '\0';
	}
	free(src);
	return (result);
}

char	*gnl_strdup(char *s)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i++] != '\0')
		;
	dest = malloc(i * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*free_and_return(void *return_val, char *str1, char *str2, char **str3)
{
	char	*result;

	if (str1 != NULL)
		free(str1);
	if (str2 != NULL)
		free(str2);
	if (str3 != NULL && *str3 != NULL)
	{
		free(*str3);
		*str3 = NULL;
	}
	if (return_val != NULL)
	{
		result = gnl_strdup(return_val);
		free(return_val);
		return (result);
	}
	return (return_val);
}
