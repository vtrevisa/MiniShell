/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:38:39 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/15 18:30:27 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	iscmd(t_data *data, char *line_splitted)
{
	char	*tmp;
	char	*cmd;
	int		index;
	
	index = -1;
	while (data->paths[++index])
	{
		tmp = ft_strjoin(data->paths[index], "/");
		cmd = ft_strjoin(tmp, line_splitted);
		if (access(cmd, X_OK) == 0)
		{
			free (tmp);
			free(cmd);
			return (1);
		}
		free (cmd);
		free (tmp);
	}
	return (0);
}

int	isarg(t_data *data, char *line_splitted)
{
	int index;

	index = 0;
	if (line_splitted[0] == '-' || line_splitted[0] == '"')
		return (1);
	else
		return (0);
}

int	issimble(t_data *data, char *line_splitted)
{
	if (line_splitted[0] == '$')
		return (3);
	else if (line_splitted[0] == '>')
	{
		data->file_fds_index++;
		if (line_splitted[1] == '>')
			return (4);
		return (5);
	}
	else if (line_splitted[0] == '<')
	{
		data->file_fds_index++;
		if (line_splitted[1] == '<')
			return (6);
		return (7);
	}
	else if (line_splitted[0] == '|')
		return (8);
	else
		return (0);
}