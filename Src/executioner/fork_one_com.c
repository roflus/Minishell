/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_one_com.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/17 19:55:23 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_out_file_one_command(t_node *command_table, t_vars *vars, \
									t_envp *env_list)
{
	int	status;

	find_path(vars);
	g_vars2.pid = fork();
	if (g_vars2.pid == -1)
		perror("fork error\n");
	if (g_vars2.pid == 0)
	{
		if (command_table->infile != NULL)
			open_infile(vars, command_table);
		if (command_table->outfile != NULL)
			open_outfile(vars, command_table);
		close_files(vars, command_table);
		q_preform_cmd(command_table, vars, env_list);
	}
	else
	{
		wait(&status);
		if (vars->f1)
			close(vars->f1);
		if (vars->f2)
			close(vars->f2);
		if (WIFEXITED(status))
			g_vars2.exitcode = WEXITSTATUS(status);
	}
}

void	just_infile_fork_process(t_node *command_table, t_vars *vars, \
									t_envp *env_list)
{
	int	status;

	find_path(vars);
	g_vars2.pid = fork();
	if (g_vars2.pid == -1)
		perror("fork error\n");
	if (g_vars2.pid == 0)
	{
		if (command_table->infile != NULL)
			open_infile(vars, command_table);
		close_files(vars, command_table);
		q_preform_cmd(command_table, vars, env_list);
	}
	else
	{
		wait(&status);
		if (vars->f1)
			close(vars->f1);
		if (WIFEXITED(status))
			g_vars2.exitcode = WEXITSTATUS(status);
	}
}

void	just_outfile_fork_process(t_node *command_table, t_vars *vars, \
										t_envp *env_list)
{	
	int	status;

	find_path(vars);
	g_vars2.pid = fork();
	if (g_vars2.pid == -1)
		perror("fork error\n");
	if (g_vars2.pid == 0)
	{
		if (command_table->outfile != NULL)
			open_outfile(vars, command_table);
		close_files(vars, command_table);
		q_preform_cmd(command_table, vars, env_list);
	}
	else
	{
		wait(&status);
		if (vars->f2)
			close(vars->f2);
		if (WIFEXITED(status))
			g_vars2.exitcode = WEXITSTATUS(status);
	}
}
