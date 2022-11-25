/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 10:56:36 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/16 13:47:43 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_var_here_doc(char *input, t_envp *env)
{
	char	*output;
	char	*var;
	char	**split;
	int		i;

	i = 0;
	output = ft_strdup(" ");
	split = ft_split(input, ' ');
	while (split[i] != NULL)
	{
		if (split[i][0] == '$' && split[i][1] != '\0')
		{
			var = ft_substr(split[i], 1, ft_strlen(split[i]));
			var = env_var(env, var);
			output = ft_strjoin_free(output, var);
			free(var);
		}
		else
			output = ft_strjoin_free(output, split[i]);
			output = ft_strjoin_free(output, " ");
		i++;
	}
	freesplit(split);
	free(input);
	return (output);
}

static void	write_in_file(int fd, char *delimiter, t_envp *env)
{
	char	*input;
	int		flag;

	flag = 0;
	while (flag == 0)
	{
		input = readline("> ");
		if (input == NULL)
			flag = 1;
		else if (ft_strncmp(input, delimiter, ft_strlen(input)) == 0 && \
			ft_strlen(input) != 0 && ft_strlen(delimiter) == ft_strlen(input))
			flag = 1;
		else if ((ft_strncmp(input, "", ft_strlen(input)) == 0) && \
				ft_strncmp(delimiter, "", ft_strlen(delimiter)) == 0)
			flag = 1;
		else
		{
			input = env_var_here_doc(input, env);
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
		}
		if (input)
			free(input);
	}
}

static int	find_end(char *split, int i)
{
	while (split[i] != ' ' && split[i] != '\0')
	{
		if (split[i] == 34)
		{
			i++;
			while (split[i] != '\0' && split[i] != 34)
				i++;
		}
		else if (split[i] == 39)
		{
			i++;
			while (split[i] != '\0' && split[i] != 39)
				i++;
		}
		else
			i++;
	}
	return (i);
}

int	list_heredoc(t_node **temp, char *split, int i, t_envp *env)
{
	char	*delimiter;
	int		fd;
	int		start;
	int		nd;

	start = i;
	i = find_end(split, i);
	nd = i;
	if (split[i - 1] == ' ')
		nd = nd - 1;
	delimiter = delimiter_without_quotes(ft_substr(split, start, (nd - start)));
	fd = open("tmpfile", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	(*temp)->heredoc = ft_strdup("active");
	write_in_file(fd, delimiter, env);
	if (split[i] == ' ')
			i++;
	close(fd);
	free(delimiter);
	return (i);
}
