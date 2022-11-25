/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:36:34 by qfrederi      #+#    #+#                 */
/*   Updated: 2021/12/13 16:36:35 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(long n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	number;
	int		len;

	number = n;
	len = length(number);
	if (number == 0)
		return (ft_strdup("0"));
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	len--;
	result[len + 1] = '\0';
	if (number < 0)
	{
		result[0] = '-';
		number = number * -1;
	}
	while (number > 0)
	{
		result[len] = (number % 10) + '0';
		number = number / 10;
		len--;
	}
	return (result);
}
