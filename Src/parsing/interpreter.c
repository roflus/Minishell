/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interpreter.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 16:22:48 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/17 18:55:10 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_in(t_node *temp)
{
	temp->words = ft_strdup("");
	temp->infile = NULL;
	temp->outfile = NULL;
	temp->heredoc = NULL;
}

int	redirect_here_doc(t_node *temp, char *split, int i, t_envp *env)
{
	char	*word;

	if (split[i + 2] == '\0')
	{
		word = ft_substr(split, i, 2);
		add_to_word(&temp, word);
		i = i + 2;
		free(word);
	}
	else
	{
		i = i + 2;
		while (split[i] == ' ')
			i++;
		if (split[i] == '\0')
		{
			(*temp).words = ft_strjoin_free((*temp).words, "<<");
			return (i);
		}
		else
			i = list_heredoc(&temp, split, i, env);
	}
	return (i);
}

int	redirect_infile(t_node *temp, char *split, int i)
{
	char	*word;

	if (split[i + 1] == '\0')
	{
		word = ft_substr(split, i, 1);
		add_to_word(&temp, word);
		free(word);
		i++;
	}
	else
		i = list_infile(&temp, i, split);
	return (i);
}

int	redirect_outfile(t_node *temp, char *split, int i)
{
	char	*word;

	if (split[i + 1] == '\0')
	{
		word = ft_substr(split, i, 2);
		add_to_word(&temp, word);
		free(word);
		i = i + 2;
	}
	else if (split[i] == '>' && split[i + 1] == '>')
	{
		temp->append = 1;
		i++;
		i = list_outfile(&temp, i, split);
	}
	else
		i = list_outfile(&temp, i, split);
	return (i);
}

void	split_pipe(char *split, t_node *temp, t_envp *env)
{
	int		i;

	i = 0;
	fill_in(temp);
	while (split[i] != '\0')
	{
		i = split_word(&temp, i, split, env);
		if (split[i] == 39)
		{
			i++;
			i = list_single_quote(&temp, i, split);
		}
		else if (split[i] == 34)
		{
			i++;
			i = list_double_quote(&temp, i, split, env);
		}
		else if (split[i] == '<' && split[i + 1] == '<')
			i = redirect_here_doc(temp, split, i, env);
		else if (split[i] == '>')
			i = redirect_outfile(temp, split, i);
		else if (split[i] == '<')
			i = redirect_infile(temp, split, i);
	}
}
