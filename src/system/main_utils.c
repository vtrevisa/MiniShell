/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:46:37 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/10 01:45:14 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	fd_error_b(t_data *data, int flag)
{
	char	*str;

	str = ft_strjoin("minishell: ", data->cmd_redir[0][flag] + 1);
	perror(str);
	free(str);
	data->rcode = 1;
	return (1);
}

int	if_data_cmd_redir0(t_data *data, int *fd, int flag)
{
	if (flag == 0)
	{
		if (data->cmd_redir[0][0][0] == '0')
			*fd = open(data->cmd_redir[0][0] + 1, O_WRONLY | O_CREAT, 0664);
		else
			*fd = open(data->cmd_redir[0][0] + 1, O_WRONLY | O_APPEND, 0664);
		if (*fd == -1)
			return (fd_error_b(data, 0));
		data->saved_stdout = dup(STDOUT_FILENO);
		dup2(*fd, STDOUT_FILENO);
		close(*fd);
	}
	else
	{
		dup2(data->saved_stdout, STDOUT_FILENO);
		close(data->saved_stdout);
	}
	return (0);
}

int	if_data_cmd_redir1(t_data *data, int *fd, int flag)
{
	if (flag == 0)
	{
		if (data->cmd_redir[0][1][0] == '0')
			*fd = open(data->cmd_redir[0][1] + 1, O_RDONLY);
		if (*fd == -1)
			return (fd_error_b(data, 1));
		data->saved_stdin = dup(STDIN_FILENO);
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	else
	{
		dup2(data->saved_stdin, STDIN_FILENO);
		close(data->saved_stdin);
	}
	return (0);
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
	data->flag_fullcmd = 0;
}

void	if_ctrl_c1(t_data *data)
{
	data->ctrl_c = 0;
	dup2(data->saved_stdin, STDIN_FILENO);
	close(data->saved_stdin);
}
