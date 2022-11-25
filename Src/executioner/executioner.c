/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:33:18 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/17 19:54:49 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	q_preform_cmd(t_node *command_table, t_vars *vars, t_envp *env_list)
{
	if ((ft_strncmp("exit", command_table->command[0], 4) == 0) \
		&& ft_strlen("exit") == ft_strlen(command_table->command[0]))
		exit_program(command_table);
	else if ((commands_built(command_table, vars, env_list) == 0))
	{
		if (!command_table->command)
			print_error(command_table, vars);
		right_path(command_table, vars);
		if (!vars->my_path)
			print_error(command_table, vars);
		if (execve(vars->my_path, command_table->command, \
			vars->enviroment) < 0)
			print_error(command_table, vars);
	}
	else
		exit(g_vars2.exitcode);
}

void	multiple_fork(t_node *command_table, t_vars *vars, t_envp *env_list)
{
	int	**fd;

	fd = malloc_pipes(vars);
	vars->com_count = 1;
	init_pipes(fd, vars);
	find_path(vars);
	first_child(command_table, fd, vars, env_list);
	command_table = command_table->next;
	while (vars->com_count < (vars->com - 1))
	{
		middle_child(command_table, fd, vars, env_list);
		vars->com_count++;
		command_table = command_table->next;
	}
	last_child(command_table, fd, vars, env_list);
	close_pipes(fd, vars);
	ft_wait(vars);
	freepipes(fd, vars);
}

static	void	no_inoutfile(t_node *command_table, t_vars *vars, \
							t_envp *env_list)
{
	int	status;

	find_path(vars);
	g_vars2.pid = fork();
	if (g_vars2.pid == -1)
		perror("fork error\n");
	if (g_vars2.pid == 0)
		q_preform_cmd(command_table, vars, env_list);
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			g_vars2.exitcode = WEXITSTATUS(status);
	}
}

void	q_pipex_start(t_node *command_table, t_vars *vars, t_envp *env_list)
{
	vars->com = lstsize(command_table);
	if (vars->com == 1 && command_table->infile == NULL \
		&& command_table->outfile == NULL)
		no_inoutfile(command_table, vars, env_list);
	else if (vars->com == 1 && command_table->infile != NULL \
			&& command_table->outfile == NULL)
		just_infile_fork_process(command_table, vars, env_list);
	else if (vars->com == 1 && command_table->infile == NULL \
			&& command_table->outfile != NULL)
		just_outfile_fork_process(command_table, vars, env_list);
	else if (vars->com == 1 && command_table->infile != NULL \
			&& command_table->outfile != NULL)
		in_out_file_one_command(command_table, vars, env_list);
	else
		multiple_fork(command_table, vars, env_list);
	freesplit(vars->path);
}
