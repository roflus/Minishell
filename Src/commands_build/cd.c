/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/17 19:10:00 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_old_pwd(t_envp *temp, char *old_content, t_envp *list)
{
	if (temp)
		refill_node(temp, old_content);
	else
	{
		lstadd_back_envp(&list, old_content);
		temp = lstlast_envp(list);
		key_output(old_content, &temp);
	}
}

static void	change_env_pwd(char *old, t_envp *list, t_vars *vars)
{
	char	new[PATH_MAX];
	char	*new_content;
	char	*old_content;
	t_envp	*temp;

	getcwd(new, PATH_MAX);
	new_content = ft_strjoin("PWD=", new);
	old_content = ft_strjoin("OLDPWD=", old);
	temp = get_node(list, "PWD");
	if (temp)
		refill_node(temp, new_content);
	else
	{
		lstadd_back_envp(&list, new_content);
		temp = lstlast_envp(list);
		key_output(new_content, &temp);
	}
	temp = get_node(list, "OLDPWD");
	change_old_pwd(temp, old_content, list);
	envp_to_array(list, vars);
	export_array(vars, list);
	free(new_content);
	free(old_content);
}

static char	*its_home(t_envp *env)
{
	t_envp	*temp;

	temp = get_node(env, "HOME");
	if (temp == NULL)
	{
		ft_putendl_fd("Minishell: cd: Home not set", 2);
		g_vars2.exitcode = 1;
		return (NULL);
	}
	return (temp->output);
}

static	char	*open_folder_utils(t_node *command_table, t_vars *vars, \
									t_envp *env)
{
	if (command_table->command[1] == NULL)
		return (its_home(env));
	else if (ft_strncmp(command_table->command[1], "~", 1) == 0)
		return (getenv("HOME"));
	else if (ft_strncmp(command_table->command[1], "-", 1) == 0)
	{
		if (vars->last_dir == NULL)
		{
			ft_putstr_fd("Minishell: cd: No last directory\n", 2);
			g_vars2.exitcode = 1;
		}
		else
			ft_putendl_fd(vars->last_dir, 1);
		return (vars->last_dir);
	}
	return (command_table->command[1]);
}

int	open_folder(t_node *command_table, t_envp *env, t_vars *vars)
{
	DIR				*dir;
	char			temp[PATH_MAX];
	char			*path;

	getcwd(temp, sizeof(temp));
	path = open_folder_utils(command_table, vars, env);
	if (path != NULL)
	{
		dir = opendir(path);
		if (dir == NULL)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			perror(path);
			g_vars2.exitcode = 1;
			return (1);
		}
		if (dir != NULL)
			closedir(dir);
		chdir(path);
		change_env_pwd(temp, env, vars);
		if (vars->last_dir != NULL)
			free(vars->last_dir);
		vars->last_dir = ft_strdup(temp);
	}
	return (1);
}
