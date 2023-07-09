/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:49:22 by romachad          #+#    #+#             */
/*   Updated: 2023/07/10 00:19:04 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	child_start(t_pipe *args, t_data *data)
{
	int	fd;

	if (data->qtd_cmd > 1)
		dup2(args->pipes[1], STDOUT_FILENO);
	if (data->cmd_redir[args->cmd_n][1])
		if (if_cmdredir_childstart_case1(&fd, data, args) == 1)
			return (1); //--> curiosamente o errno eh 2, mas o bash retorna 1...
	if (data->cmd_redir[args->cmd_n][0])
		if (if_cmdredir_childstart_case2(&fd, data, args) == 1)
			return (1);
	close_pipes(args, data);
	if (args->builtin == 0)
	{
		execve(args->fpath, data->full_cmd[args->cmd_n], data->envp);
		/* printf("sai do execve\n"); */
		free(args->fpath);
	}
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
	{
		if (data->cmd_redir[args->cmd_n][0][0] == '0')
			fd = open(data->cmd_redir[args->cmd_n][0] + 1, O_WRONLY | O_CREAT);
		else
			fd = open(data->cmd_redir[args->cmd_n][0] + 1, O_WRONLY | O_APPEND | O_CREAT);
		if (fd == -1)
			return (fd_error(data, args));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	dup2(args->pipes[args->pipe_i], STDIN_FILENO);
	dup2(args->pipes[args->pipe_i + 3], STDOUT_FILENO);
	close_pipes(args, data);
	if (args->builtin == 0)
	{
		execve(args->fpath, data->full_cmd[args->cmd_n], data->envp);
		free(args->fpath);
	}
	else
		builtin_exec_pipe(args, data);
	return (errno);
}

static int	child_end(t_pipe *args, t_data *data)
{
	int	fd;

	dup2(args->pipes[args->pipe_i], STDIN_FILENO);
	if (data->cmd_redir[args->cmd_n][1])
		if (if_cmdredir_childend_case1(&fd, data, args) == 1)
			return (1);
	if (data->cmd_redir[args->cmd_n][0])
	{
		if (data->cmd_redir[args->cmd_n][0][0] == '0')
			fd = open(data->cmd_redir[args->cmd_n][0] + 1, O_WRONLY | O_CREAT);
		else
			fd = open(data->cmd_redir[args->cmd_n][0] + 1, O_WRONLY | O_APPEND | O_CREAT);
		if (fd == -1)
			return (fd_error(data, args));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	close_pipes(args, data);
	if (args->builtin == 0)
	{
		execve(args->fpath, data->full_cmd[args->cmd_n], data->envp);
		free(args->fpath);
	}
	else
		builtin_exec_pipe(args, data);
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
	args->builtin = builtin_checker(data->full_cmd[args->cmd_n][0]);
	if (args->builtin == 0)
	{
		args->fpath = path_search(data->envp, data->full_cmd[args->cmd_n][0]);
		/*if (args->fpath == NULL)
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			ft_printf("minishell: %s: command not found\n", \
		data->full_cmd[args->cmd_n][0]);
			close_pipes(args, data);
			return (127);
		}
		if (access(args->fpath, X_OK) != 0)
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			ft_printf("minishell: %s: Permission denied\n", args->fpath);
			close_pipes(args, data);
			return (126);
		}*/
		code = check_perm_cmd(args, data);
		if (code != 0)
			return (code);
	}
	return (child_exec(args, data));
}
