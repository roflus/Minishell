/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:38:30 by qfrederi      #+#    #+#                 */
/*   Updated: 2021/12/13 16:38:30 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_dstswitch(char *dst, const void *src, size_t len)
{
	size_t	i;
	char	*source;
	char	*destination;

	i = 0;
	source = (char *)src;
	destination = (char *)dst;
	while (i < len)
	{
		destination[i] = source[i];
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*source;
	char	*destination;

	source = (char *)src;
	destination = (char *)dst;
	if (!len || dst == src)
		return (dst);
	if (destination > source)
	{
		while (len > 0)
		{
			len--;
			destination[len] = source[len];
		}
	}
	else
	{
		ft_dstswitch(dst, src, len);
	}	
	return (dst);
}
