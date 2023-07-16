/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:54:48 by romachad          #+#    #+#             */
/*   Updated: 2023/07/16 08:44:05 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	call_fork(t_pipe *args, t_data *data)
{
	args->pid[args->cmd_n] = fork();
	if (args->pid[args->cmd_n] == 0)
	{
		args->pid[args->cmd_n] = child_prog(args, data);
		data->rcode = args->pid[args->cmd_n];
		close_pipes(args, data);
		free_args(args);
		free_char_array(data->envp);
		exit_child(data, data->rcode);
	}
	if (args->pid[args->cmd_n] > 0)
		return (0);
	else
		return (-1);
}

static void	pipe_to_pipe(t_pipe *args, t_data *data)
{
	int	retv;
	int	i;

	args->flag = 2;
	i = -1;
	while (++i < data->qtd_cmd - 2)
	{
		retv = call_fork(args, data);
		if (retv < 0)
		{
			free_args(args);
			exit_child(data, 255);
		}
		args->cmd_n++;
		args->pipe_i += 2;
	}
}

static void	wait_pipes(t_pipe *args, t_data *data)
{
	/*int	num_exited;
	pid_t	exited_pid;
	int	status;
	int	exit_status;

	num_exited = 0;
	data->ctrl_c = 1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, sigquit_parent);
	while (num_exited < args->cmd_n)
	{
		exited_pid = waitpid(-1, &status, 0);
		if (exited_pid > 0)
		{
			num_exited++;
			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				printf("pid[%d] rcode= %d\n",exited_pid,exit_status);
				data->rcode = exit_status;
			}
			else if (WIFSIGNALED(status))
			{
				exit_status = WTERMSIG(status);
				printf("pid[%d] rcode= %d\n",exited_pid,exit_status);
				data->rcode = 128 + WTERMSIG(status);
			}
		}
	}
	data->ctrl_c = 0;
	data->is_here_doc = 0;*/



	int	i;
	int	status;
	int	exit_status;

	i = -1;
	data->ctrl_c = 1;
	while (++i < args->cmd_n)
	{
		//signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, sigquit_parent);
		waitpid(args->pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			//printf("pid[%d] rcode= %d\n",i,exit_status);
			data->rcode = exit_status;
		}
		else if (WIFSIGNALED(status))
		{
			exit_status = WTERMSIG(status);
			//printf("pid[%d] rcode= %d\n",i,exit_status);
			data->rcode = 128 + WTERMSIG(status);
		}
	}
	data->ctrl_c = 0;
	data->is_here_doc = 0;
}

static int	main_fork(t_pipe *args, t_data *data)
{
	args->flag = 0;
	call_fork(args, data);
	args->cmd_n++;
	if (data->qtd_cmd > 2)
		pipe_to_pipe(args, data);
	if (data->qtd_cmd > 1)
	{
		args->flag = 1;
		call_fork(args, data);
		args->cmd_n++;
	}
	close_pipes(args, data);
	wait_pipes(args, data);
	free_args(args);
	return (0);
}

void	piper(t_data *data)
{
	t_pipe	args;

	args.pipes = malloc((data->qtd_cmd * 2) * sizeof(data->qtd_cmd));
	if (args.pipes == NULL)
		error_exit("Fail pipes malloc");
	if (create_pipes(&args, data) == -1)
	{
		ft_printf("ERROR! Failed to create pipes!\n");
		free(args.pipes);
		exit (130);
	}
	args.pid = malloc(data->qtd_cmd * sizeof(data->qtd_cmd));
	if (args.pid == NULL)
		error_exit("Fail pid malloc");
	args.cmd_n = 0;
	args.pipe_i = 0;
	main_fork(&args, data);
}
