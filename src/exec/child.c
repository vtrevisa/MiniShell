/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:49:22 by romachad          #+#    #+#             */
/*   Updated: 2023/07/16 00:33:17 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	child_start(t_pipe *args, t_data *data)
{
	int	fd;

	if (data->qtd_cmd > 1)
	{
		if (data->is_here_doc == 1)
			dup2(args->pipes[3], STDOUT_FILENO);
		else
			dup2(args->pipes[1], STDOUT_FILENO);
	}
	if (data->cmd_redir[args->cmd_n][1])
		if (if_cmdredir_childstart_case1(&fd, data, args) == 1)
			return (1);
	if (data->cmd_redir[args->cmd_n][0])
		if (if_cmdredir_childstart_case2(&fd, data, args) == 1)
			return (1);
	close_pipes(args, data);
	if (args->builtin == 0)
		call_exec(data, args);
	else
		builtin_exec_pipe(args, data);
	if (args->builtin == 0)
		return (errno);
	else
		return (data->rcode);
}

static int	child_middle(t_pipe *args, t_data *data)
{
	int	fd;

	if (data->cmd_redir[args->cmd_n][1])
		if (if_cmdredir_childmiddle_case1(&fd, data, args) == 1)
			return (1);
	if (data->cmd_redir[args->cmd_n][0])
		if (if_cmd_redir(data, args, &fd))
			return (fd_error(data, args));
	if (data->is_here_doc == 1)
	{
		dup2(args->pipes[args->pipe_i + 2], STDIN_FILENO);
		dup2(args->pipes[args->pipe_i + 5], STDOUT_FILENO);
	}
	else
	{
		dup2(args->pipes[args->pipe_i], STDIN_FILENO);
		dup2(args->pipes[args->pipe_i + 3], STDOUT_FILENO);
	}
	close_pipes(args, data);
	if (args->builtin == 0)
		call_exec(data, args);
	else
		return (builtin_exec_pipe(args, data));
	return (errno);
}

static int	child_end(t_pipe *args, t_data *data)
{
	int	fd;

	if (data->is_here_doc == 1)
		dup2(args->pipes[args->pipe_i + 2], STDIN_FILENO);
	else
		dup2(args->pipes[args->pipe_i], STDIN_FILENO);
	if (data->cmd_redir[args->cmd_n][1])
		if (if_cmdredir_childend_case1(&fd, data, args) == 1)
			return (1);
	if (data->cmd_redir[args->cmd_n][0])
	{
		if (if_cmd_redir(data, args, &fd))
			return (fd_error(data, args));
	}
	close_pipes(args, data);
	if (args->builtin == 0)
	{
		execve(args->fpath, data->full_cmd[args->cmd_n], data->envp);
		free(args->fpath);
	}
	else
		return (builtin_exec_pipe(args, data));
	return (errno);
}

static int	child_exec(t_pipe *args, t_data *data)
{
	if (args->flag == 0)
		return (child_start(args, data));
	if (args->flag == 2)
		return (child_middle(args, data));
	else
		return (child_end(args, data));
}

int	child_prog(t_pipe *args, t_data *data)
{
	int	code;

	data->rcode = 0;
	if (data->cmd_redir[args->cmd_n][0])
		if (data->cmd_redir[args->cmd_n][0][0] == '2')
			return (1);
	if (data->cmd_redir[args->cmd_n][1])
		if (data->cmd_redir[args->cmd_n][1][0] == '2')
			return (1);
	args->builtin = builtin_checker(data->full_cmd[args->cmd_n][0]);
	if (args->builtin == 0)
	{
		args->fpath = path_search(data->envp, \
	data->full_cmd[args->cmd_n][0], data);
		if (data->rcode == 127)
			return (data->rcode);
		code = check_perm_cmd(args, data);
		if (code != 0)
			return (code);
	}
	return (child_exec(args, data));
}
