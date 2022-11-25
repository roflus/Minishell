/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 12:11:17 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/16 18:57:25 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_node *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

static t_node	*lstlast(t_node *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static t_node	*lstnew(char *split)
{
	t_node	*newcontent;

	newcontent = (t_node *)malloc(sizeof(t_node));
	if (!newcontent)
		return (NULL);
	newcontent->content = ft_strdup(split);
	newcontent->words = NULL;
	newcontent->infile = NULL;
	newcontent->outfile = NULL;
	newcontent->heredoc = NULL;
	newcontent->command = NULL;
	newcontent->append = 0;
	newcontent->cancel = 0;
	newcontent->next = NULL;
	free(split);
	return (newcontent);
}

void	lstadd_back(t_node **lst, char *split)
{
	t_node	*temp;
	t_node	*new;

	new = lstnew(split);
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = lstlast(*lst);
		temp->next = new;
	}
}

t_node	*create_head(char *first)
{
	t_node	*head;

	head = (t_node *)malloc(sizeof(t_node));
	if (head == NULL)
	{
		ft_putstr_fd("Error with creating list.\n", 2);
		exit(1);
	}
	head->content = ft_strdup(first);
	head->words = NULL;
	head->infile = NULL;
	head->outfile = NULL;
	head->heredoc = NULL;
	head->command = NULL;
	head->append = 0;
	head->cancel = 0;
	head->next = NULL;
	free(first);
	return (head);
}
