/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here-doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 00:49:21 by romachad          #+#    #+#             */
/*   Updated: 2023/07/24 01:32:33 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*add_line(char *new, char *current)
{
	char	*str;
	char	*copy;

	if (current && *current)
	{
		str = ft_strjoin(current, "\n");
		copy = str;
		str = ft_strjoin(copy, new);
	}
	else
		str = ft_strdup(new);
	if (current)
	{
		if (*current)
			free(copy);
		free(current);
	}
	return (str);
}

static char	*add_new_line(char *str, int *flag)
{
	char	*new;

	if (str && flag == 0)
	{
		new = ft_strjoin(str, "\n");
		free(str);
	}
	else
	{
		if (*flag == 0)
		{
			new = ft_strjoin(str, "\n");
			free(str);
		}
		else
			return (str);
	}
	return (new);
}

static void	if_read_while_heredoc(char *str, char *read, \
		char **new_line, int *flag)
{
	if (ft_strlen(read))
	{
		if (ft_strncmp(str + 1, read, ft_strlen(str + 1) + \
	ft_strlen(read)) == 0)
		{
			if (**new_line == 0)
				*flag = 1;
			*new_line = add_new_line(*new_line, flag);
		}
		else
			*new_line = add_line(read, *new_line);
	}
	else
		*new_line = add_new_line(*new_line, flag);
}

static void	while_heredoc(char *str, char *read, char **new_line, int *flag)
{
	while (ft_strncmp(str + 1, read, ft_strlen(str + 1) + ft_strlen(read)) != 0)
	{
		if (read)
			free(read);
		read = readline("> ");
		if (read != NULL)
			if_read_while_heredoc(str, read, new_line, flag);
		else
		{
			if (g_var.ctrl_c == 1)
				break ;
			*new_line = add_new_line(*new_line, 0);
			ft_printf("minishell: warning: ");
			ft_printf("here-document delimited by end-of-file");
			ft_printf(" (wanted `%s')\n", str + 1);
			break ;
		}
	}
}

char	*here_doc(char *str)
{
	char	*read;
	char	*new_line;
	int		flag;

	flag = 0;
	g_var.here_doc = 1;
	g_var.saved_stdin = dup(STDIN_FILENO);
	new_line = ft_calloc(1, sizeof(new_line));
	read = ft_calloc(1, sizeof(read));
	while_heredoc(str, read, &new_line, &flag);
	free(str);
	if (g_var.ctrl_c == 0)
		close(g_var.saved_stdin);
	read = ft_strjoin("1", new_line);
	g_var.here_doc = 0;
	free(new_line);
	g_var.is_here_doc = 1;
	return (read);
}
