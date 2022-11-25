/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:40:40 by qfrederi      #+#    #+#                 */
/*   Updated: 2021/12/13 16:40:40 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	while ((i >= 0))
	{
		if (s[i] == (unsigned char) c)
		{
			return ((char *)s + i);
		}
		i--;
	}
	return (NULL);
}
