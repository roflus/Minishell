/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:39:20 by qfrederi      #+#    #+#                 */
/*   Updated: 2021/12/13 16:39:22 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		++i;
	}
	if (s[i] == (unsigned char) c)
	{
		return ((char *)s + i);
	}
	return (NULL);
}
