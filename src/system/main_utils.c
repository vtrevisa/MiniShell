/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:46:37 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/03 00:53:17 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	if_data_cmd_redir0(t_data *data, int *fd, int flag)
{
	if (flag == 0)
	{
		data->saved_stdout = dup(STDOUT_FILENO);
		if (data->cmd_redir[0][0][0] == '0')
			*fd = open(data->cmd_redir[0][0] + 1, O_WRONLY);
		else
			*fd = open(data->cmd_redir[0][0] + 1, O_WRONLY | O_APPEND);
		dup2(*fd, STDOUT_FILENO);
		close(*fd);
	}
	else
	{
		dup2(data->saved_stdout, STDOUT_FILENO);
		close(data->saved_stdout);
	}
}

void	if_data_cmd_redir1(t_data *data, int *fd, int flag)
{
	if (flag == 0)
	{
		data->saved_stdin = dup(STDIN_FILENO);
		if (data->cmd_redir[0][1][0] == '0')
			*fd = open(data->cmd_redir[0][1] + 1, O_RDONLY);
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	else
	{
		dup2(data->saved_stdin, STDIN_FILENO);
		close(data->saved_stdin);
	}
}

void	free_full_cmd(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (data->full_cmd[++i])
	{
		free_char_array(data->full_cmd[i]);
		while (++j < 2)
			free(data->cmd_redir[i][j]);
		j = -1;
		free(data->cmd_redir[i]);
	}
}

void	if_ctrl_c1(t_data *data)
{
	data->ctrl_c = 0;
	dup2(data->saved_stdin, STDIN_FILENO);
	close(data->saved_stdin);
}
