/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:05:07 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/21 13:24:38 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	if_cmdredir_childstart_case1(int *fd, t_data *data, t_pipe *args)
{
	if (data->cmd_redir[args->cmd_n][1][0] == '0')
	{
		*fd = open(data->cmd_redir[args->cmd_n][1] + 1, O_RDONLY);
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	else
	{
		dup2(args->pipes[0], STDIN_FILENO);
		write(args->pipes[1], data->cmd_redir[args->cmd_n][1] + 1, \
	ft_strlen(data->cmd_redir[args->cmd_n][1] + 1));
	}
}

void	if_cmdredir_childstart_case2(int *fd, t_data *data, t_pipe *args)
{
	if (data->cmd_redir[args->cmd_n][0][0] == '0')
		*fd = open(data->cmd_redir[args->cmd_n][0] + 1, O_WRONLY);
	else
		*fd = open(data->cmd_redir[args->cmd_n][0] + 1, O_WRONLY | O_APPEND);
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

void	if_cmdredir_childmiddle_case1(int *fd, t_data *data, t_pipe *args)
{
	if (data->cmd_redir[args->cmd_n][1][0] == '0')
	{
		*fd = open(data->cmd_redir[args->cmd_n][1] + 1, O_RDONLY);
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	else
	{
		dup2(args->pipes[args->pipe_i + 2], STDIN_FILENO);
		write(args->pipes[args->pipe_i + 3], data->cmd_redir[args-> \
	cmd_n][1] + 1, ft_strlen(data->cmd_redir[args->cmd_n][1] + 1));
	}
}

void	if_cmdredir_childend_case1(int *fd, t_data *data, t_pipe *args)
{
	if (data->cmd_redir[args->cmd_n][1][0] == '0')
	{
		*fd = open(data->cmd_redir[args->cmd_n][1] + 1, O_RDONLY);
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	else
	{
		dup2(args->pipes[args->pipe_i + 2], STDIN_FILENO);
		write(args->pipes[args->pipe_i + 3], data->cmd_redir \
	[args->cmd_n][1] + 1, ft_strlen(data->cmd_redir[args->cmd_n][1] + 1));
	}
}
