/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_to_array.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/08 13:34:59 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	lst_size(t_envp *list)
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

static int	lst_size2(t_envp *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->output == NULL)
			i--;
		list = list->next;
		i++;
	}
	return (i);
}

void	envp_to_array(t_envp *env, t_vars *vars)
{
	int		i;
	int		count;

	if (vars->enviroment != NULL)
		freesplit(vars->enviroment);
	count = lst_size2(env);
	i = 0;
	vars->enviroment = malloc((count + 1) * sizeof(char *));
	if (vars->enviroment == NULL)
		pexit("error", 1);
	while (i < count)
	{
		if (env->output == NULL)
			env = env->next;
		vars->enviroment[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	vars->enviroment[i] = NULL;
	vars->env_count = count;
}
