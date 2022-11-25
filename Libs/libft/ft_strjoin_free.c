/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 18:09:09 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/16 13:34:27 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief joins two strings and frees s1
 * 
 * @param s1 string to join
 * @param s2 
 * @return char* 
 */
char	*ft_strjoin_free(char *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	i;
	char	*join;

	i = 0;
	s1len = ft_strlen (s1);
	s2len = ft_strlen (s2);
	join = malloc (s1len + s2len + 1);
	if (join == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{	
		join[s1len + i] = s2[i];
		i++;
	}
	join[s1len + s2len] = '\0';
	free(s1);
	return (join);
}
