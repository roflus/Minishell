/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 15:35:29 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/08 16:08:20 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*lstlast_envp(t_envp *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static t_envp	*lstnew_envp(char *split)
{
	t_envp	*newcontent;

	newcontent = (t_envp *)malloc(sizeof(t_envp));
	if (!newcontent)
		return (NULL);
	newcontent->content = ft_strdup(split);
	newcontent->key = NULL;
	newcontent->output = NULL;
	newcontent->next = NULL;
	return (newcontent);
}

void	lstadd_back_envp(t_envp **lst, char *split)
{
	t_envp	*temp;
	t_envp	*new;

	new = lstnew_envp(split);
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = lstlast_envp(*lst);
		temp->next = new;
	}
}

t_envp	*create_head_envp(char *first)
{
	t_envp	*head;

	head = (t_envp *)malloc(sizeof(t_envp));
	if (head == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	head->content = ft_strdup(first);
	head->key = NULL;
	head->output = NULL;
	head->next = NULL;
	return (head);
}

t_envp	*put_envp_in_list(char **envp)
{
	t_envp	*envi;
	t_envp	*temp;
	int		i;

	envi = create_head_envp(envp[0]);
	i = 1;
	while (envp[i] != NULL)
	{
		lstadd_back_envp(&envi, envp[i]);
		i++;
	}
	i = 0;
	temp = envi;
	while (temp != NULL)
	{
		key_output(envp[i], &temp);
		temp = temp->next;
		i++;
	}
	return (envi);
}
