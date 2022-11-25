/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 11:28:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/16 11:07:47 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pexit(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

static void	print_error_dir(t_node *command_table, DIR *dir)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(command_table->command[0], 2);
	ft_putstr_fd(": is a directory\n", 2);
	closedir(dir);
	exit(126);
}

void	print_error(t_node *command_table, t_vars *vars)
{
	DIR		*dir;

	if (access(command_table->command[0], X_OK) != 0 \
				&& command_table->command[0][0] == '.' \
				&& command_table->command[0][1] == '/')
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command_table->command[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (vars->my_path == NULL && \
		(ft_strncmp(command_table->command[0], "cat", 4) != 0))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command_table->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	dir = opendir(command_table->command[0]);
	if (dir)
		print_error_dir(command_table, dir);
	exit(1);
}
