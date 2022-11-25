/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interpreter_files.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 13:37:38 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/17 18:42:23 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_close(int fd, t_node *temp)
{
	if (temp->append == 1)
	{
		fd = open(temp->outfile, O_RDWR | O_APPEND);
		if (fd < 0)
			fd = open(temp->outfile, \
				O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	else
		fd = open(temp->outfile, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(temp->outfile);
		g_vars2.exitcode = 1;
	}
	close(fd);
}

static void	list_outfile_een(t_node *temp, char *outfile)
{
	int	fd;

	fd = 0;
	if (temp->outfile)
		free(temp->outfile);
	temp->outfile = ft_strdup(outfile);
	if (temp->cancel == 0)
		open_close(fd, temp);
	free(outfile);
}

int	list_outfile(t_node **temp, int i, char *split)
{
	char	*outfile;
	int		start;
	int		end;

	i++;
	while (split[i] == ' ')
		i++;
	start = i;
	while (split[i] != '\0')
	{
		if (split[i] == ' ')
		{
			end = i;
			outfile = ft_substr(split, start, (end - start));
			list_outfile_een((*temp), outfile);
			i = another_outfile(temp, i, split);
			return (i);
		}
		i++;
	}
	end = i;
	outfile = ft_substr(split, start, (end - start));
	list_outfile_een((*temp), outfile);
	return (i);
}

static void	list_infile_een(t_node *temp, char *infile)
{
	if (temp->infile)
		free(temp->infile);
	temp->infile = ft_strdup(infile);
	if (access(temp->infile, R_OK) != 0)
		temp->cancel = 1;
	free(infile);
}

int	list_infile(t_node **temp, int i, char *split)
{
	char	*infile;
	int		start;
	int		end;

	while (split[++i] == ' ')
		;
	start = i;
	while (split[i] != '\0')
	{
		if (split[i] == ' ')
		{
			end = i;
			infile = ft_substr(split, start, (end - start));
			list_infile_een((*temp), infile);
			if ((*temp)->cancel == 1)
				break ;
			i = another_infile(temp, i, split);
			return (i);
		}
		i++;
	}
	end = i;
	infile = ft_substr(split, start, (end - start));
	list_infile_een((*temp), infile);
	return (i);
}
