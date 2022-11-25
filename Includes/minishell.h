/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:42:30 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/17 17:43:39 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/signal.h>
# include <dirent.h>
# include <limits.h>
# include <termios.h>

typedef struct s_vars
{
	int		f1;
	int		f2;
	int		no_infile;
	int		no_outfile;
	int		env_count;
	char	*slash;
	char	*pipex_path;
	char	**enviroment;
	char	**cmd;
	char	**path;
	char	*path_cmd;
	char	*my_path;
	char	**export_env;
	int		com;
	int		com_count;
	char	*last_dir;
	char	*command_export;
}	t_vars;

typedef struct s_vars2
{
	int		pid;
	int		exitcode;
}	t_vars2;

extern t_vars2	g_vars2;

typedef struct s_node
{
	char			*content;
	char			*words;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	char			**command;
	int				append;
	int				cancel;

	struct s_node	*next;
}	t_node;

typedef struct s_envp
{
	char			*content;
	char			*key;
	char			*output;

	struct s_envp	*next;
}	t_envp;

void	main_loop(int flag, t_envp *env, t_vars *vars);
void	free_command(t_node *list);

// Commands_build
		// cd.c
int		open_folder(t_node *command_table, t_envp *env, t_vars *vars);

		// commands.c
int		commands_built(t_node *command_table, t_vars *vars, t_envp *env_list);
int		builtin(t_node *command_table, t_envp *env, t_vars *vars);
int		pwd(void);
int		env(t_vars *vars);

		// echo_n.c
int		echo_n(t_node *command_table);
int		is_option(char *string, int i);

		//echo.c
int		echo(t_node *command_table);

		// exit.c
int		exit_now_questionmark(t_node *node, t_vars *vars, t_envp *env);
void	exit_program(t_node *command_table);
int		exit_program_error(char **arguments);

		// exit_utils.c
int		digits_only(char *string);
int		exit_argument_check(char **arguments);

		// export_array.c
void	export_array(t_vars *vars, t_envp *env);

		// export.c
void	export_add_list(t_envp *env_list, t_vars *vars);
void	refill_node(t_envp *node, char *string);
t_envp	*get_node(t_envp *env_list, char *string);
void	export_add_back(t_envp *env_list, t_vars *vars);
void	export(t_envp *env_list, t_node *command_table, t_vars *vars);

		// export_command.c
int		find_command(char *content, int i, t_vars *vars, t_envp *env_list);

		// export_command_var.c
int		find_var_export(int i, char *content, t_vars *vars, t_envp *env);
int		find_key_var_export(int i, char *content, t_vars *vars, t_envp *env);

		// export_command_key.c
int		export_key_var(char *content, int i, t_vars *vars, t_envp *env_list);
int		export_key_no_var(char *content, int i, t_vars *vars);
int		has_space_num(char *string);
int		export_first_char_check(char c);
int		string_check_export(char *string);

		// export_unset_utils.c
void	export_unset_array(t_envp *env_list, t_vars *vars);
void	unset_number_identifier(t_vars *vars);
void	export_number_identifier(t_vars *vars);
int		has_equal(char *string);

		// unset.c
void	unset(t_envp *env_list, t_node *command_table, t_vars *vars);

// environment
		// env_to_array.c
int		lst_size(t_envp *list);
void	envp_to_array(t_envp *env, t_vars *vars);
void	free_envp(t_envp *list);

		// env_var.c
void	print_envp(t_envp *list);
char	*env_var(t_envp *list, char *var);
void	key_output(char *split, t_envp **temp);

		// envp list
t_envp	*lstlast_envp(t_envp *lst);
void	lstadd_back_envp(t_envp **lst, char *split);
t_envp	*create_head_envp(char *first);
t_envp	*put_envp_in_list(char **envp);

// executioner
		// executioner.c
void	q_preform_cmd(t_node *command_table, t_vars *vars, t_envp *env_list);
void	multiple_fork(t_node *command_table, t_vars *vars, t_envp *env_list);
void	q_pipex_start(t_node *command_table, t_vars *vars, t_envp *env_list);

		// child.c
void	first_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list);
void	middle_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list);
void	last_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list);

		// fork_one_com.c
void	just_infile_fork_process(t_node *command_table, t_vars *vars, \
									t_envp *env_list);	
void	just_outfile_fork_process(t_node *command_table, t_vars *vars, \
										t_envp *env_list);
void	in_out_file_one_command(t_node *command_table, t_vars *vars, \
									t_envp *env_list);

		// get_path.c
void	right_path(t_node *command_table, t_vars *vars);
void	find_path(t_vars *vars);
char	*q_find_token_infile(t_node *command_table, t_vars *vars);
char	*q_find_token_outfile(t_node *command_table, t_vars *vars);

		// init_pipes.c
int		**malloc_pipes(t_vars *vars);
void	init_pipes(int **fd, t_vars *vars);
void	close_pipes(int **fd, t_vars *vars);
void	ft_wait(t_vars *vars);
void	just_exit(int **fd, t_vars *vars, t_node *command_table);

		// open_files.c
void	openfiles(t_node *command_table, t_vars *vars);
void	open_infile(t_vars *vars, t_node *command_table);
void	open_outfile(t_vars *vars, t_node *command_table);
void	close_files(t_vars *vars, t_node *command_table);

		// pipex_error.c
void	print_error(t_node *command_table, t_vars *vars);
void	pexit(char *str, int exit_code);

// parsing
		// create_command_table.c
void	exec_init(t_node *command_table);
t_node	*create_command_table_list(char *split, t_envp *env);
void	command_table(char *split, t_envp *env, t_vars *vars);
int		make_pipes(char *split, int i);
int		add_to_list(t_node *node, int i, char *split);

		// here_doc.c
int		list_heredoc(t_node **temp, char *split, int i, t_envp *env);

		// here_doc_utils.c
char	*delimiter_without_quotes(char *delimiter);
char	*ft_strjoin_free_both(char *s1, char *s2);

		// interpreter_file.c
int		list_outfile(t_node **temp, int i, char *split);
int		list_infile(t_node **temp, int i, char *split);

		// interpreter_util.c
int		find_var(t_node **temp, int i, char *split, t_envp *env);
int		var_first_char(char *split, int i, t_node **temp);
int		another_outfile(t_node **temp, int i, char *split);
int		another_infile(t_node **temp, int i, char *split);

		// interpreter.c
void	list_print_command(t_node *list);
int		redirect_infile(t_node *temp, char *split, int i);
int		redirect_here_doc(t_node *temp, char *split, int i, t_envp *env);
int		redirect_outfile(t_node *temp, char *split, int i);
void	split_pipe(char *split, t_node *temp, t_envp *env);

		// list.c
int		lstsize(t_node *list);
void	lstadd_back(t_node **lst, char *split);
t_node	*create_head(char *first);

		// quotes.c
void	add_to_word(t_node **temp, char *word);
int		find_quote(t_node **temp, int i, char *split, int start);
int		list_double_quote(t_node **temp, int i, char *split, t_envp *env);
int		list_single_quote(t_node **temp, int i, char *split);
int		var_in_double_quotes(t_node **temp, int i, char *split, t_envp *env);

		// words.c
int		split_word(t_node **temp, int i, char *split, t_envp *env);
int		find_word(t_node **temp, int i, char *split, int start);
void	add_to_word_split(t_node **temp, char *word, int space);
void	add_space(t_node **temp, char *split, int start);

		// signals
void	signals(void);
void	signals_quit(void);
void	sig_handler(int sign);

		//signals_utils;
void	check_signals(void);

		//free
void	freesplit(char **split);
void	free_command(t_node *list);
void	freepipes(int **fd, t_vars *vars);
void	free_env_list(t_envp *list);

#endif