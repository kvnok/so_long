/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:32:59 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/16 18:01:10 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*strjoin_free(char **s1, char **s2)
{
	int		s1len;
	int		s2len;
	int		i;
	char	*s3;

	s1len = int_strlen(*s1);
	s2len = int_strlen(*s2);
	i = 0;
	s3 = malloc_and_bzero((s1len + s2len + 1), 1);
	if (s3 == NULL)
		return (NULL);
	while (i < s1len + s2len)
	{
		if (i < s1len)
			s3[i] = (*s1)[i];
		else
			s3[i] = (*s2)[i - s1len];
		i++;
	}
	s3[i] = '\0';
	free(*s1);
	return (s3);
}

char	*save(char **line, char **afternewline)
{
	int	spot;
	int	linelen;

	spot = find_newline(*line);
	linelen = int_strlen(*line);
	if (spot == -1 || linelen == 0)
		return (NULL);
	*afternewline = cut_free(line, spot + 1, linelen - spot, afternewline);
	if (*afternewline == NULL)
		return (cleanup(line, afternewline));
	line[0][spot + 1] = '\0';
	return (*afternewline);
}

char	*reading(int fd, char *buffer, char **line, char **afternewline)
{
	int	amount;

	amount = 1;
	while (find_newline(*line) == -1 && amount != 0)
	{
		amount = read(fd, buffer, BUFFER_SIZE);
		if (amount <= -1)
			return (NULL);
		buffer[amount] = '\0';
		if (amount == 0)
			break ;
		*line = strjoin_free(line, &buffer);
		if (*line == NULL)
			return (NULL);
	}
	save(line, afternewline);
	return (*line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	static char	*afternewline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc_and_bzero((BUFFER_SIZE + 1), 1);
	if (line == NULL)
		return (cleanup(&line, &afternewline));
	if (afternewline != NULL)
	{
		line = strjoin_free(&line, &afternewline);
		if (line == NULL)
			return (cleanup(&line, &afternewline));
		afternewline[0] = '\0';
	}
	if (reading(fd, buffer, &line, &afternewline) == NULL)
	{
		buffer[0] = '\0';
		return (cleanup(&line, &afternewline));
	}
	if (line[0] == '\0')
		return (cleanup(&line, &afternewline));
	return (line);
}
