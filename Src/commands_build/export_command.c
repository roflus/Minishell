/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/16 17:02:03 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_command_single_quote(int i, char *content, t_vars *vars)
{
	int	start;

	i++;
	start = i;
	while (content[i] != 39 && content[i] != '\0')
		i++;
	vars->command_export = ft_strjoin_free_both(vars->command_export, \
		ft_substr(content, start, i - start));
	if (content[i + 1] != '\0')
		i++;
	return (i);
}

static int	find_command_double_quotes(int i, char *content, t_vars *vars, \
		t_envp *env_list)
{
	int	start;

	i++;
	start = i;
	while (content[i] != 34 && content[i] != '\0')
	{
		if (content[i] == '$' && (content[i + 1] != ' ' && \
			content[i + 1] != '\0' && content[i + 1] != 34))
		{
			vars->command_export = ft_strjoin_free_both(vars->command_export, \
				ft_substr(content, start, i - start));
			i++;
			i = find_var_export(i, content, vars, env_list);
			start = i;
		}
		else
			i++;
	}
	vars->command_export = ft_strjoin_free_both(vars->command_export, \
		ft_substr(content, start, i - start));
	if (content[i + 1] != '\0')
		i++;
	return (i);
}

static int	find_command_no_quotes(int i, char *content, t_vars *vars, \
		t_envp *env_list)
{
	int	start;

	start = i;
	while (content[i] != ' ' && content[i] != '\0')
	{
		if (content[i] == 39 || content[i] == 34)
			break ;
		else if (content[i] == '$' && (content[i + 1] != ' ' \
			&& content[i + 1] != '\0'))
			break ;
		i++;
	}
	if (content[i] == '$' && (content[i + 1] != ' ' \
			&& content[i + 1] != '\0'))
	{
		vars->command_export = ft_strjoin_free_both(vars->command_export, \
		ft_substr(content, start, i - start));
		i++;
		i = find_var_export(i, content, vars, env_list);
	}
	else
		vars->command_export = ft_strjoin_free_both(vars->command_export, \
		ft_substr(content, start, i - start));
	return (i);
}

int	find_command(char *content, int i, t_vars *vars, t_envp *env_list)
{
	if (content[i] == '$' && (content[i + 1] != ' ' \
			&& content[i + 1] != '\0'))
		i = export_key_var(content, i, vars, env_list);
	else
		i = export_key_no_var(content, i, vars);
	if (content[i] == '\0' || content[i] == ' ')
		return (i);
	i++;
	vars->command_export = ft_strjoin_free(vars->command_export, "=");
	while (content[i] != '\0' && content[i] != ' ')
	{
		if (content[i] == 39)
			i = find_command_single_quote(i, content, vars);
		else if (content[i] == 34)
			i = find_command_double_quotes(i, content, vars, env_list);
		else
			i = find_command_no_quotes(i, content, vars, env_list);
	}
	return (i);
}
