/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:05:07 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/14 20:15:02 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	fd_error(t_data *data, t_pipe *args)
{
	char	*str;

	str = ft_strjoin("minishell: ", data->cmd_redir[args->cmd_n][1] + 1);
	perror(str);
	free(str);
	close_pipes(args, data);
	if (args->builtin == 0)
		free(args->fpath);
	return (1);
}

int	if_cmdredir_childstart_case1(int *fd, t_data *data, t_pipe *args)
{
	if (data->cmd_redir[args->cmd_n][1][0] == '0')
	{
		*fd = open(data->cmd_redir[args->cmd_n][1] + 1, O_RDONLY);
		if (*fd == -1)
			return (fd_error(data, args));
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	else
	{
		dup2(args->pipes[0], STDIN_FILENO);
		write(args->pipes[1], data->cmd_redir[args->cmd_n][1] + 1, \
	ft_strlen(data->cmd_redir[args->cmd_n][1] + 1));
	}
	return (0);
}

int	if_cmdredir_childstart_case2(int *fd, t_data *data, t_pipe *args)
{
	if (data->cmd_redir[args->cmd_n][0][0] == '0')
		*fd = open(data->cmd_redir[args->cmd_n][0] + 1, \
	O_WRONLY | O_CREAT, 0664);
	else
		*fd = open(data->cmd_redir[args->cmd_n][0] + 1, \
	O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (*fd == -1)
		return (fd_error(data, args));
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
	return (0);
}

int	if_cmdredir_childmiddle_case1(int *fd, t_data *data, t_pipe *args)
{
	if (data->cmd_redir[args->cmd_n][1][0] == '0')
	{
		*fd = open(data->cmd_redir[args->cmd_n][1] + 1, O_RDONLY);
		if (*fd == -1)
			return (fd_error(data, args));
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	else
	{
		dup2(args->pipes[args->pipe_i + 2], STDIN_FILENO);
		write(args->pipes[args->pipe_i + 3], data->cmd_redir[args-> \
	cmd_n][1] + 1, ft_strlen(data->cmd_redir[args->cmd_n][1] + 1));
	}
	return (0);
}

int	if_cmdredir_childend_case1(int *fd, t_data *data, t_pipe *args)
{
	if (data->cmd_redir[args->cmd_n][1][0] == '0')
	{
		*fd = open(data->cmd_redir[args->cmd_n][1] + 1, O_RDONLY);
		if (*fd == -1)
			return (fd_error(data, args));
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	else
	{
		dup2(args->pipes[args->pipe_i + 2], STDIN_FILENO);
		write(args->pipes[args->pipe_i + 3], data->cmd_redir \
	[args->cmd_n][1] + 1, ft_strlen(data->cmd_redir[args->cmd_n][1] + 1));
	}
	return (0);
}
