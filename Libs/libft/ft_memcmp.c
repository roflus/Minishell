/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:38:17 by qfrederi      #+#    #+#                 */
/*   Updated: 2021/12/13 16:38:18 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p;
	const unsigned char	*q;
	size_t				i;

	p = (const unsigned char *)s1;
	q = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p[i] != q[i])
		{
			return (p[i] - q[i]);
		}
		i++;
	}
	return (0);
}
