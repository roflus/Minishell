/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 13:25:38 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/08 13:41:58 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	size_t	i;
	char	*join;

	i = 0;
	join = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{	
		join[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	join[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	free(s2);
	return (join);
}

static char	*find_output_here_doc(char *delimiter, \
			char *output, int i, int start)
{
	if (output == NULL)
		output = ft_substr(delimiter, start, (i - start));
	else
		output = ft_strjoin_free_both(output, \
					(ft_substr(delimiter, start, (i - start))));
	return (output);
}

char	*delimiter_without_quotes(char *del)
{
	char	*output;
	int		start;
	int		i;

	i = 0;
	output = NULL;
	if (del[0] == 39 || del[0] == 34)
	{
		i++;
		while ((del[i] == 39 || del[i] == 34) && del[i] != '\0')
			i++;
	}
	start = i;
	while (del[i] != '\0')
	{
		if (del[i] == 39 || del[i] == 34)
		{
			output = find_output_here_doc(del, output, i, start);
			start = i + 1;
		}
		i++;
	}
	output = find_output_here_doc(del, output, i, start);
	free(del);
	return (output);
}
