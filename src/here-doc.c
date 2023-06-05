/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here-doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 00:49:21 by romachad          #+#    #+#             */
/*   Updated: 2023/06/04 21:03:38 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"



static char	*add_line(char *new, char *current)
{
	char	*str;
	char	*copy;

	if (current)
	{
		str = ft_strjoin(current, "\n");
		copy = str;
		str = ft_strjoin(copy, new);
	}
	else
		str = ft_strdup(new);
	if (current)
	{
		free(copy);
		free(current);
	}
	return (str);
}

static char	*add_new_line(char *str)
{
	char	*new;

	if (str)
	{
		new = ft_strjoin(str, "\n");
		free(str);
	}
	else
		new = ft_strdup("\n");
	return (new);
}

char	*here_doc(char *str)
{
	char	*read;
	char	*new_line;

	new_line = NULL;
	read = ft_calloc(1, sizeof(read));
	//while (ft_strncmp(str+1, read, ft_strlen(str+1)) != 0 && ft_strlen(str+1) != ft_strlen(read))
	while (ft_strncmp(str+1, read, ft_strlen(str+1) + ft_strlen(read)) != 0)
	{
		if (read)
			free(read);
		//read = readline("> ");
		if ((read = readline("> ")) != NULL)
		{
			if (ft_strlen(read))
			{
				if (ft_strncmp(str+1, read, ft_strlen(str+1) + ft_strlen(read)) == 0)
					new_line = add_new_line(new_line);
				else
					new_line = add_line(read, new_line);
			}
			else
				new_line = add_new_line(new_line);
		}
		else
		{
			new_line = add_new_line(new_line);
			ft_printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')", str+1);
			break;
		}
	}
	free(str);
	free(read);
	read = ft_strjoin("1", new_line);
	free(new_line);
	return (read);
}
