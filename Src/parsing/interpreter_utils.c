/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interpreter_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 12:32:33 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/17 18:36:40 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	another_outfile(t_node **temp, int i, char *split)
{
	if (split[i + 1] == '>')
	{
		i++;
		i = redirect_outfile(*temp, split, i);
	}
	return (i);
}

int	another_infile(t_node **temp, int i, char *split)
{
	if (split[i + 1] == '<')
	{
		i++;
		i = redirect_infile(*temp, split, i);
	}
	return (i);
}

int	var_first_char(char *split, int i, t_node **temp)
{
	char	*tempo;

	tempo = ft_itoa(g_vars2.exitcode);
	if ((ft_isdigit(split[i]) == 1))
		i++;
	else if (split[i] == '?')
	{
		i++;
		add_to_word(temp, tempo);
	}
	free(tempo);
	return (i);
}

int	find_var(t_node **temp, int i, char *split, t_envp *env)
{
	char	*var;
	int		start;

	i = var_first_char(split, i, temp);
	if ((ft_isdigit(split[i - 1]) != 1) && split[i - 1] != '?')
	{
		start = i;
		while (split[i] != ' ')
		{
			i++;
			if (split[i] == 34 || split[i] == '.' || split[i] == '$' || \
				split[i] == '\0' || split[i] == 39)
				break ;
		}
		var = ft_substr(split, start, (i - start));
		var = env_var(env, var);
		add_to_word(temp, var);
	}
	if (split[i] == '$')
	{
		i++;
		i = find_var(temp, i, split, env);
	}
	return (i);
}
