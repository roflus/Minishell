/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:38:34 by qfrederi      #+#    #+#                 */
/*   Updated: 2021/12/13 16:38:35 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*pointer;

	i = 0;
	pointer = (unsigned char *)b;
	while (i < len)
	{
		*pointer = (unsigned char)c;
		i++;
		pointer++;
	}
	return (b);
}
