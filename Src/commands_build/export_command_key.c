/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_command_key.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 18:15:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/17 17:44:09 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_key_var(char *content, int i, t_vars *vars, t_envp *env_list)
{
	int	start;

	i++;
	start = i;
	i = find_key_var_export(i, content, vars, env_list);
	return (i);
}

int	export_key_no_var(char *content, int i, t_vars *vars)
{
	int	start;

	start = i;
	while (content[i] != '\0' && content[i] != '=' && content[i] != ' ')
			i++;
	if (content[i] == '\0' || content[i] == ' ')
	{
		vars->command_export = ft_substr(content, start, i - start);
		return (i);
	}
	vars->command_export = ft_substr(content, start, i - start);
	return (i);
}

int	has_space_num(char *string)
{
	int	i;

	i = 6;
	while (string[i] != '\0')
	{
		if (string[i] != ' ')
		{
			if (ft_isdigit(string[i]) == 1 || string[i] == '!')
				return (2);
		}
		else
			return (1);
		i++;
	}
	return (0);
}

int	export_first_char_check(char c)
{
	if (ft_isalpha(c) == 1 || c == '_' || c == '\0')
		return (1);
	else
		return (0);
}

int	string_check_export(char *string)
{
	int	i;

	i = 1;
	while (string[i] != '\0')
	{	
		if (string[i] == '=')
			break ;
		if (ft_isalpha(string[i]) == 0 && \
			ft_isalnum(string[i]) == 0 && string[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
