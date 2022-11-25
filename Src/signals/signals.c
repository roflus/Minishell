/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 17:33:32 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/14 10:06:45 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_int(int sign)
{
	struct termios	t;

	if (sign == SIGINT)
	{
		tcgetattr(0, &t);
		t.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &t);
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_vars2.exitcode = 1;
	}
}

static void	process_signal_else(int sign)
{
	if (sign == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_vars2.exitcode = 0;
	}
	else if (sign == SIGQUIT)
		signal(SIGQUIT, SIG_IGN);
}

static void	process_signal(int sign)
{
	if (!kill(g_vars2.pid, sign))
	{
		if (sign == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			g_vars2.exitcode = 131;
		}
		else if (sign == SIGINT)
		{
			ft_putstr_fd("\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			g_vars2.exitcode = 130;
		}
	}
	else
		process_signal_else(sign);
}

void	sig_handler(int sign)
{
	if ((sign == SIGINT || sign == SIGQUIT) \
		&& g_vars2.pid != 0)
		process_signal(sign);
	else if (sign == SIGQUIT)
		signal(SIGQUIT, SIG_IGN);
	else if (sign == SIGINT)
		sig_int(sign);
}

void	signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
