/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 14:29:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/14 15:23:29 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_path(t_vars *vars)
{
	char	*temp;
	int		i;

	i = 0;
	while (ft_strncmp("PATH=", vars->enviroment[i], 5) \
			&& i + 1 < vars->env_count)
		i++;
	temp = ft_strtrim(vars->enviroment[i], "PATH=");
	vars->path = ft_split(temp, ':');
	free(temp);
	if (!vars->path)
		perror("nopath");
}

static void	right_path_loop(t_node *command_table, t_vars *vars, int i)
{
	while (vars->path[i] != NULL)
	{
		vars->slash = ft_strjoin(vars->path[i], "/");
		if (!vars->slash)
			print_error(command_table, vars);
		vars->pipex_path = ft_strjoin(vars->slash, command_table->command[0]);
		if (!vars->pipex_path)
			print_error(command_table, vars);
		if (access(vars->pipex_path, X_OK) == 0)
		{
			vars->my_path = ft_strdup(vars->pipex_path);
			free(vars->slash);
			free(vars->pipex_path);
			break ;
		}
		free(vars->slash);
		free(vars->pipex_path);
		i++;
	}
}

void	right_path(t_node *command_table, t_vars *vars)
{
	int		i;

	vars->my_path = NULL;
	if (access(command_table->command[0], X_OK) == 0)
		vars->my_path = ft_strdup(command_table->command[0]);
	i = 0;
	right_path_loop(command_table, vars, i);
	if (vars->my_path == NULL)
		print_error(command_table, vars);
}

char	*q_find_token_infile(t_node *command_table, t_vars *vars)
{
	t_node	*temp;

	vars->no_infile = 0;
	temp = command_table;
	while (temp)
	{
		if (temp->infile != NULL)
			return (temp->infile);
		temp = temp->next;
	}
	vars->no_infile = 1;
	return ("");
}

char	*q_find_token_outfile(t_node *command_table, t_vars *vars)
{
	t_node	*temp;

	vars->no_outfile = 0;
	temp = command_table;
	while (temp != NULL)
	{
		if (temp->outfile != NULL)
			return (temp->outfile);
		temp = temp->next;
	}
	vars->no_outfile = 1;
	return ("");
}
