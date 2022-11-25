/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/14 16:46:53 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_vars(t_vars *vars)
{
	vars->f1 = 0;
	vars->f2 = 0;
	vars->no_infile = 0;
	vars->no_outfile = 0;
	vars->env_count = 0;
	vars->enviroment = NULL;
	vars->cmd = NULL;
	vars->path = NULL;
	vars->path_cmd = NULL;
	vars->my_path = NULL;
	vars->com = 0;
	vars->com_count = 0;
	vars->export_env = NULL;
	vars->last_dir = NULL;
	vars->command_export = NULL;
	vars->slash = NULL;
	vars->pipex_path = NULL;
}

char	*rl_history(void)
{
	static char	*input;

	if (input)
	{
		free (input);
		input = (char *) NULL;
	}
	input = readline("Minishell RQ4.0: ");
	if (input != NULL)
		input[ft_strlen(input) + 1] = '\0';
	if (input && *input)
		add_history (input);
	return (input);
}

void	main_loop(int flag, t_envp *env, t_vars	*vars)
{
	char			*input;

	while (flag != EOF)
	{
		signal(SIGQUIT, SIG_IGN);
		g_vars2.pid = 0;
		input = rl_history();
		signals();
		if (input == NULL)
		{
			flag = EOF;
			ft_putstr_fd("exit\n", 2);
		}
		else if (input != NULL)
			command_table(input, env, vars);
	}
}

void	set_shlvl(t_envp *env)
{
	t_envp	*temp;
	char	*trim;
	char	*tempstr;
	int		lvl;

	temp = get_node(env, "SHLVL");
	trim = ft_strtrim(temp->content, "SHLVL=");
	lvl = ft_atoi(trim) + 1;
	tempstr = ft_itoa(lvl);
	free(temp->content);
	temp->content = ft_strjoin("SHLVL=", tempstr);
	free(tempstr);
	free(trim);
	free(temp->key);
	free(temp->output);
	key_output(temp->content, &temp);
}

t_vars2	g_vars2;

int	main(int argc, char *argv[], char **envp)
{
	t_envp	*env;
	t_vars	*vars;

	if (argc == 1 && argv[0] != NULL)
	{
		vars = (t_vars *)malloc(sizeof(t_vars));
		if (vars == NULL)
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		init_vars(vars);
		env = put_envp_in_list(envp);
		set_shlvl(env);
		envp_to_array(env, vars);
		export_array(vars, env);
		check_signals();
		signals();
		main_loop(0, env, vars);
	}
	return (0);
}
