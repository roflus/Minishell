/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:39:29 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/26 18:39:18 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*destination;
	char		*pointer;
	size_t		len;

	len = 0;
	while (s1[len])
	{
		len++;
	}
	destination = malloc(len + 1);
	if (destination == NULL)
		return (destination);
	pointer = destination;
	while (*s1)
	{
		*pointer = *s1;
		pointer++;
		s1++;
	}
	*pointer = '\0';
	return (destination);
}
