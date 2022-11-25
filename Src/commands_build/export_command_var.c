/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_command_var.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 14:09:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/16 17:01:54 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_first_char_export(char *content, int i)
{
	if ((ft_isdigit(content[i]) == 1))
		i++;
	else if (content[i] == '?')
		i++;
	return (i);
}

int	find_var_export(int i, char *content, t_vars *vars, t_envp *env)
{
	char	*var;
	int		start;

	i = var_first_char_export(content, i);
	if ((ft_isdigit(content[i - 1]) != 1) && content[i - 1] != '?')
	{
		start = i;
		while (content[i] != ' ')
		{
			i++;
			if (content[i] == 34 || content[i] == '.' || content[i] == '$' || \
				content[i] == '\0' || content[i] == 39)
				break ;
		}
		var = ft_substr(content, start, (i - start));
		var = env_var(env, var);
		vars->command_export = ft_strjoin_free(vars->command_export, var);
	}
	if (content[i] == '$')
	{
		i++;
		i = find_var_export(i, content, vars, env);
	}
	return (i);
}

int	find_key_var_export(int i, char *content, t_vars *vars, t_envp *env)
{
	char	*var;
	int		start;

	i = var_first_char_export(content, i);
	if ((ft_isdigit(content[i - 1]) != 1) && content[i - 1] != '?')
	{
		start = i;
		while (content[i] != ' ')
		{
			i++;
			if (content[i] == 34 || content[i] == '.' || content[i] == '$' || \
				content[i] == '\0' || content[i] == 39 || content[i] == '=')
				break ;
		}
		var = ft_substr(content, start, (i - start));
		var = env_var(env, var);
		vars->command_export = ft_strdup(var);
	}
	if (content[i] == '$')
	{
		i++;
		i = find_var_export(i, content, vars, env);
	}
	return (i);
}
