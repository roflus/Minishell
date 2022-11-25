/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_array.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 13:38:36 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/01 13:42:04 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_env(t_vars *vars, t_envp *env)
{
	int		i;
	int		count;

	i = 0;
	count = lst_size(env);
	vars->export_env = malloc((count + 1) * sizeof(char *));
	if (vars->export_env == NULL)
		pexit("error", 1);
	while (i < count)
	{
		vars->export_env[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	vars->export_env[i] = NULL;
	return (count);
}

static void	sort_array(char **array, int arraylength)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < arraylength)
	{
		j = 0;
		while (j < arraylength - 1 - i)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{	
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	export_array(t_vars *vars, t_envp *env)
{
	int		arraylength;

	if (vars->export_env != NULL)
		freesplit(vars->export_env);
	arraylength = copy_env(vars, env);
	sort_array(vars->export_env, arraylength);
}
