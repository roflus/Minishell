/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 12:30:51 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/11 12:39:25 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	digits_only(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '-')
			i++;
		if (ft_isdigit((int)string[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	exit_argument_check(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		if (i >= 2)
			return (0);
		i++;
	}
	return (1);
}
