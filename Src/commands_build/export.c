/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/17 18:15:44 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_add_list(t_envp *env_list, t_vars *vars)
{
	t_envp	*temp2;

	temp2 = get_node(env_list, vars->command_export);
	if (temp2)
	{
		if (has_equal(vars->command_export) > 0)
			refill_node(temp2, vars->command_export);
	}
	else
		export_add_back(env_list, vars);
}

t_envp	*get_node(t_envp *env_list, char *string)
{
	t_envp	*temp;
	size_t	lenght;

	temp = env_list;
	lenght = has_equal(string);
	if (lenght == 0)
		lenght = ft_strlen(string);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, string, lenght) == 0 && \
			(ft_strlen(temp->key) == lenght))
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

void	refill_node(t_envp *node, char *string)
{
	free(node->content);
	free(node->key);
	if (node->output)
		free(node->output);
	node->content = ft_strdup(string);
	key_output(string, &node);
}

void	export_add_back(t_envp *env_list, t_vars *vars)
{
	t_envp	*temp;

	lstadd_back_envp(&env_list, vars->command_export);
	temp = lstlast_envp(env_list);
	key_output(vars->command_export, &temp);
}

void	export(t_envp *env_list, t_node *command_table, t_vars *vars)
{
	int	i;

	i = 7;
	while (command_table->content[i] != '\0')
	{
		i = find_command(command_table->content, i, vars, env_list);
		if (export_first_char_check(vars->command_export[0]) == 0)
			export_number_identifier(vars);
		else if (string_check_export(vars->command_export) == 1)
			export_number_identifier(vars);
		else
			export_add_list(env_list, vars);
		free(vars->command_export);
		if (command_table->content[i] == '\0')
			break ;
		else
			i++;
	}
	export_unset_array(env_list, vars);
}
