/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here-doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 00:49:21 by romachad          #+#    #+#             */
/*   Updated: 2023/07/10 11:23:06 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

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

static void	if_read_while_heredoc(char *str, char *read, char **new_line)
{
	if (ft_strlen(read))
	{
		if (ft_strncmp(str + 1, read, ft_strlen(str + 1) + \
	ft_strlen(read)) == 0)
			*new_line = add_new_line(*new_line);
		else
			*new_line = add_line(read, *new_line);
	}
	else
		*new_line = add_new_line(*new_line);
}

static void	while_heredoc(char *str, char *read, char **new_line)
{
	while (ft_strncmp(str + 1, read, ft_strlen(str + 1) + ft_strlen(read)) != 0)
	{
		if (read)
			free(read);
		read = readline("> ");
		if (read != NULL)
			if_read_while_heredoc(str, read, new_line);
		else
		{
			if (g_var.ctrl_c == 1)
				break ;
			*new_line = add_new_line(*new_line);
			break ;
		}
	}
}

char	*here_doc(char *str)
{
	char	*read;
	char	*new_line;

	g_var.here_doc = 1;
	g_var.saved_stdin = dup(STDIN_FILENO);
	new_line = NULL;
	read = ft_calloc(1, sizeof(read));
	while_heredoc(str, read, &new_line);
	free(str);
	if (g_var.ctrl_c == 0)
		close(g_var.saved_stdin);
	read = ft_strjoin("1", new_line);
	g_var.here_doc = 0;
	free(new_line);
	return (read);
}
