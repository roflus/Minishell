/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:06:14 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/08 13:35:04 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list)
{
	g_vars2.pid = fork();
	if (g_vars2.pid < 0)
		print_error(command_table, vars);
	if (g_vars2.pid == 0)
	{
		if (command_table->infile != NULL)
			open_infile(vars, command_table);
		if (command_table->outfile != NULL)
			open_outfile(vars, command_table);
		else
		{
			if (dup2(fd[0][1], STDOUT_FILENO) == -1)
				print_error(command_table, vars);
		}
		if (!command_table->command[0])
			just_exit(fd, vars, command_table);
		else
		{
			close_pipes(fd, vars);
			close_files(vars, command_table);
			q_preform_cmd(command_table, vars, env_list);
		}
	}
}

void	middle_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list)
{
	g_vars2.pid = fork();
	if (g_vars2.pid < 0)
		print_error(command_table, vars);
	if (g_vars2.pid == 0)
	{
		if (command_table->infile != NULL)
			open_infile(vars, command_table);
		else
			dup2(fd[vars->com_count - 1][0], STDIN_FILENO);
		if (command_table->outfile != NULL)
			open_outfile(vars, command_table);
		else
			dup2(fd[vars->com_count][1], STDOUT_FILENO);
		if (!command_table->command[0])
			just_exit(fd, vars, command_table);
		else
		{
			close_pipes(fd, vars);
			close_files(vars, command_table);
			q_preform_cmd(command_table, vars, env_list);
		}
	}
}

void	last_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list)
{
	g_vars2.pid = fork();
	if (g_vars2.pid < 0)
		print_error(command_table, vars);
	if (g_vars2.pid == 0)
	{
		if (command_table->infile != NULL)
			open_infile(vars, command_table);
		else
		{
			if (dup2(fd[vars->com_count - 1][0], STDIN_FILENO) == -1)
				print_error(command_table, vars);
		}
		if (command_table->outfile != NULL)
			open_outfile(vars, command_table);
		if (!command_table->command[0])
			just_exit(fd, vars, command_table);
		else
		{
			close_pipes(fd, vars);
			close_files(vars, command_table);
			q_preform_cmd(command_table, vars, env_list);
		}
	}
}
