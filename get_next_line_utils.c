/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:32:48 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/13 12:11:28 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	int_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*malloc_and_bzero(int count, int size)
{
	char	*ptr;
	int		i;
	int		len;

	i = 0;
	len = count * size;
	ptr = (char *) malloc(len * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*cut_free(char **s, int start, int len, char **extra)
{
	char	*cpy;
	int		i;

	cpy = malloc_and_bzero(((len + 1) * sizeof(char)), 1);
	if (cpy == NULL)
		return (NULL);
	i = start;
	while (i < start + len)
	{
		cpy[i - start] = (*s)[i];
		i++;
	}
	cpy[i - start] = '\0';
	free(*extra);
	return (cpy);
}

int	find_newline(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*cleanup(char **line, char **afternewline)
{
	if (*line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	if (*afternewline != NULL)
	{
		free(*afternewline);
		*afternewline = NULL;
	}
	return (NULL);
}
