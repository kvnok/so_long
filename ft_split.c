/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:32:38 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/13 12:11:28 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**free_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	flag;
	int	wordcount;

	i = 0;
	flag = 0;
	wordcount = 0;
	while (s[i])
	{
		if (s[i] != (unsigned char)c && flag == 0)
		{
			flag = 1;
			wordcount++;
		}
		if (s[i] == (unsigned char)c)
			flag = 0;
		i++;
	}
	return (wordcount);
}

static int	word_length(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != (unsigned char)c && s[i])
		i++;
	return (i);
}

static char	*copy_word(const char *s, char c, char *str, int *i)
{
	int	str_i;

	str_i = 0;
	while (s[*i] != (unsigned char)c && s[*i] != '\0')
	{
		str[str_i] = s[*i];
		(*i)++;
		str_i++;
	}
	str[str_i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		i;
	int		wcount;
	int		s_i;

	if (!s)
		return (NULL);
	wcount = count_words(s, c);
	i = 0;
	s_i = 0;
	strings = malloc((wcount + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	strings[wcount] = NULL;
	while (s_i < wcount)
	{
		while (s[i] == (unsigned char)c)
			i++;
		strings[s_i] = malloc((word_length(&s[i], c) + 1) * sizeof(char));
		if (!strings[s_i])
			return (free_strings(strings));
		strings[s_i] = copy_word(s, c, strings[s_i], &i);
		s_i++;
	}
	return (strings);
}
