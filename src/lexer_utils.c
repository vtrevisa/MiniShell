/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:38:39 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/04/13 17:32:28 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	iscmd(t_data *data, char *line_splitted)
{
	char	*tmp;
	int		index;
	
	index = -1;
	while (data->paths[++index])
	{
		tmp = ft_strjoin(data->paths[index], "/");
		data->cmd_path = ft_strjoin(tmp, line_splitted);
		/* ft_printf("%s\n", data->cmd_path); */
		if (access(data->cmd_path, X_OK) == 0)
		{
			free (tmp);
			return (1);
		}
		free (data->cmd_path);
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