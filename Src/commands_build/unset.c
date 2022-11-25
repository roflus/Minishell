/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/17 17:45:40 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_pos(t_envp *env_list, t_vars *vars)
{
	int	i;

	i = 0;
	while (env_list)
	{
		if ((ft_strncmp(env_list->key, vars->command_export, \
			ft_strlen(vars->command_export)) == 0) && \
			ft_strlen(vars->command_export) == ft_strlen(env_list->key))
			return (i);
		env_list = env_list->next;
		i++;
	}
	return (i);
}

static	void	unset_utils( t_envp *temp, t_envp *del, int position, int i)
{
	if (position == 0)
	{
		del = temp;
		temp = temp->next;
		del->next = NULL;
		free(del->content);
		free(del->output);
		free(del->key);
		free(del);
	}
	else
	{
		while (i < position - 1)
		{
			temp = temp->next;
			i++;
		}
		del = temp->next;
		temp->next = temp->next->next;
		del->next = NULL;
		free(del->content);
		free(del->output);
		free(del->key);
		free(del);
	}
}

static	int	find_key(t_envp *env_list, t_vars *vars)
{
	int	i;

	i = 0;
	while (env_list)
	{
		if ((ft_strncmp(env_list->key, vars->command_export, \
			ft_strlen(vars->command_export)) == 0) && \
			ft_strlen(vars->command_export) == ft_strlen(env_list->key))
			return (1);
		env_list = env_list->next;
		i++;
	}
	return (0);
}

static void	unset_key(t_envp *env_list, t_vars *vars, \
				t_envp *temp, t_envp	*del)
{
	int		position;

	position = get_pos(env_list, vars);
	unset_utils(temp, del, position, 0);
}

void	unset(t_envp *env_list, t_node *command_table, t_vars *vars)
{
	t_envp	*temp;
	t_envp	*del;
	int		i;

	del = NULL;
	temp = env_list;
	i = 6;
	while (command_table->content[i] != '\0')
	{
		i = find_command(command_table->content, i, vars, env_list);
		if (export_first_char_check(vars->command_export[0]) == 0)
			unset_number_identifier(vars);
		else if (string_check_export(vars->command_export) == 1)
			unset_number_identifier(vars);
		else
			if (find_key(env_list, vars) == 1)
				unset_key(env_list, vars, temp, del);
		free(vars->command_export);
		if (command_table->content[i] == '\0')
			break ;
		else
			i++;
	}
	export_unset_array(env_list, vars);
}
