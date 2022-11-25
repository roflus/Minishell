/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_unset_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 10:25:34 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/18 09:39:15 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_unset_array(t_envp *env_list, t_vars *vars)
{
	envp_to_array(env_list, vars);
	export_array(vars, env_list);
	vars->command_export = NULL;
}

void	unset_number_identifier(t_vars *vars)
{
	ft_putstr_fd("Minishell: unset: ", 2);
	ft_putstr_fd(vars->command_export, 2);
	ft_putstr_fd(" : not a valid identifier\n", 2);
	g_vars2.exitcode = 1;
}

void	export_number_identifier(t_vars *vars)
{
	ft_putstr_fd("Minishell: export: ", 2);
	ft_putstr_fd(vars->command_export, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	g_vars2.exitcode = 1;
}

int	has_equal(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
