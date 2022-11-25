/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:38:25 by qfrederi      #+#    #+#                 */
/*   Updated: 2021/12/13 16:38:25 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*source;
	char	*destination;

	source = (char *)src;
	destination = (char *)dst;
	if (!n || dst == src)
		return (dst);
	i = 0;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}
