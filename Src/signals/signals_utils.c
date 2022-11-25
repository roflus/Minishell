/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 11:48:13 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/11 11:56:32 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int sign)
{
	(void)sign;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	check_signals(void)
{
	signal(SIGUSR1, handler);
	kill(g_vars2.pid, SIGUSR1);
}
