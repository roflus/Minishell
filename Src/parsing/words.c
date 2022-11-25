/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   words.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 12:34:26 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/17 18:36:44 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_space(t_node **temp, char *split, int start)
{
	if (start != 0 && split[start] == ' ')
		add_to_word(temp, " ");
}

void	add_to_word_split(t_node **temp, char *word, int space)
{
	int		i;
	char	**split;

	split = ft_split(word, ' ');
	i = 0;
	while (split[i] != NULL)
	{
		(*temp)->words = ft_strjoin_free((*temp)->words, split[i]);
		if (split[i + 1] != NULL)
				(*temp)->words = ft_strjoin_free((*temp)->words, " ");
		else
		{
			if (space == 1)
				(*temp)->words = ft_strjoin_free((*temp)->words, " ");
		}
		i++;
	}
	freesplit(split);
}

int	find_word(t_node **temp, int i, char *split, int start)
{
	char	*pipe_split;
	int		end;
	int		space;

	space = 0;
	end = i;
	pipe_split = ft_substr(split, start, (end - start));
	if (split[i - 1] == ' ' && split[i] != '>' && split[i] != '<')
		space = 1;
	add_to_word_split(temp, pipe_split, space);
	free(pipe_split);
	return (i);
}

static int	word_start_space(t_node **temp, char *split, int i)
{
	add_space(temp, split, i);
	return (i);
}

int	split_word(t_node **temp, int i, char *split, t_envp *env)
{
	int		start;

	start = word_start_space(temp, split, i);
	while (split[i] != '\0')
	{
		if (split[i] == 39 || split[i] == 34 || \
			split[i] == '<' || split[i] == '>')
		{
			i = find_word(temp, i, split, start);
			return (i);
		}
		if ((split[i] == '$' && (split[i + 1] != ' ' && split[i + 1] != '\0')))
		{
			i = find_word(temp, i, split, start);
			i++;
			i = find_var(temp, i, split, env);
			if (split[i] == 39 || split[i] == 34)
				return (i);
			start = word_start_space(temp, split, i);
		}
		i++;
	}
	i = find_word(temp, i, split, start);
	return (i);
}
