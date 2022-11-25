/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 11:03:47 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/17 14:05:32 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_command(t_node *list)
{
	t_node	*temp;

	while (list != NULL)
	{
		temp = list;
		free(temp->words);
		free(temp->content);
		free(temp->heredoc);
		free(temp->infile);
		free(temp->outfile);
		freesplit(temp->command);
		free(temp);
		list = list->next;
	}
}

void	freepipes(int **fd, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->com - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	free_env_list(t_envp *list)
{
	t_envp	*temp;

	while (list != NULL)
	{
		temp = list;
		free(temp->content);
		free(temp->key);
		free(temp->output);
		free(temp);
		list = list->next;
	}
}
