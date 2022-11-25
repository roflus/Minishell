/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:39:40 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/20 16:53:38 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	i;
	char	*pointer;

	i = 0;
	s1len = ft_strlen (s1);
	s2len = ft_strlen (s2);
	pointer = malloc (s1len + s2len + 1);
	if (pointer == NULL)
		return (pointer);
	while (s1[i] != '\0')
	{
		pointer[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{	
		pointer[s1len + i] = s2[i];
		i++;
	}
	pointer[s1len + s2len] = '\0';
	return (pointer);
}
