/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:39:15 by qfrederi      #+#    #+#                 */
/*   Updated: 2021/12/13 16:39:16 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_partial_array(char **result, size_t max_index)
{
	size_t	i;

	i = 0;
	while (i <= max_index)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static char	**ft_populate_array(char const *s, char c, char **result)
{
	size_t	word_start;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		word_start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		result[j] = ft_substr(s, word_start, i - word_start);
		if (result[j] == NULL)
		{
			free_partial_array(result, j);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}

static size_t	ft_wordcount(char const *s, char c)
{
	int	total;

	total = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			total++;
			while (*s != '\0' && *s != c)
			{
				s++;
			}
		}
		else
			s++;
	}
	return (total);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	count;

	count = ft_wordcount(s, c);
	result = malloc((count + 1) * sizeof(char *));
	if (result == NULL)
		return (result);
	result = ft_populate_array(s, c, result);
	return (result);
}
