/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 13:54:02 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/20 17:42:38 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_word(t_node **temp, char *word)
{
	(*temp)->words = ft_strjoin_free((*temp)->words, word);
}

int	find_quote(t_node **temp, int i, char *split, int start)
{
	char	*pipe_split;
	int		end;

	end = i;
	pipe_split = ft_substr(split, start, (end - start));
	add_to_word(temp, pipe_split);
	free(pipe_split);
	return (i);
}

int	var_in_double_quotes(t_node **temp, int i, char *split, t_envp *env)
{
	i++;
	i = find_var(temp, i, split, env);
	if (split[i] == 34)
	{
		i++;
		return (i);
	}
	else
		return (i);
}

int	list_double_quote(t_node **temp, int i, char *split, t_envp *env)
{
	int		start;

	start = i;
	while (split[i] != '\0')
	{
		if (split[i] == 34)
		{
			i = find_quote(temp, i, split, start);
			i++;
			return (i);
		}
		else if (split[i] == '$' && (split[i + 1] != '\0' && split[i + 1] \
				!= 34 && split[i + 1] != ' '))
		{
			i = find_quote(temp, i, split, start);
			i = var_in_double_quotes(temp, i, split, env);
			if (split[i - 1] == 34)
				return (i);
			else
				start = i;
		}	
		i++;
	}
	i = find_quote(temp, i, split, start);
	return (i);
}

int	list_single_quote(t_node **temp, int i, char *split)
{
	int		start;

	start = i;
	while (split[i] != '\0')
	{
		if (split[i] == 39)
		{
			i = find_quote(temp, i, split, start);
			i++;
			return (i);
		}
		i++;
	}
	i = find_quote(temp, i, split, start);
	return (i);
}
