/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:40:54 by qfrederi      #+#    #+#                 */
/*   Updated: 2021/12/13 16:40:56 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*dst;

	slen = ft_strlen(s);
	if (len > slen - start)
		len = slen - start;
	if (start > slen || len > slen)
		return (ft_strdup(""));
	dst = malloc(len + 1);
	if (dst == NULL)
		return (dst);
	dst[len] = '\0';
	while (len > 0)
	{
		len--;
		dst[len] = s[start + len];
	}
	return (dst);
}
