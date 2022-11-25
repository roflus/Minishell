/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/14 17:30:04 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_print(t_node *command_table, char *str_to_print)
{
	if (command_table->heredoc != NULL)
	{
		str_to_print = ft_substr(command_table->words, 5, \
		(ft_strlen(command_table->words) - 12));
	}
	else
		str_to_print = ft_substr(command_table->words, 5, \
		ft_strlen(command_table->words));
	ft_putendl_fd(str_to_print, 1);
	free(str_to_print);
	return (1);
}

int	echo(t_node *command_table)
{
	char	*str_to_print;

	str_to_print = NULL;
	if (!command_table->command[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (ft_strcmp("~", command_table->command[1]) == 0)
	{
		ft_putendl_fd(getenv("HOME"), 1);
		return (1);
	}
	else if (is_option(command_table->command[1], 0) != 0)
		return (echo_n(command_table));
	else
		return (echo_print(command_table, str_to_print));
	return (1);
}
