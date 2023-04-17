/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_and_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:46:28 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/04/17 21:55:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	child_1(t_data *data)
{
	if (data->fd_in)
	{
		dup2(data->fd_in, 0);
		close(data->fd_in);
	}
	dup2(data->fd[1], 1);
	close(data->fd[0]);
	close(data->fd[1]);
	if (data->cmd)
		execve(data->cmd_path, data->line_splitted, data->envp);
	return (0);
}

int	child_2(t_data *data)
{
	dup2(data->fd[0], 0);
	dup2(data->fd[1], 1);
	close(data->fd[0]);
	close(data->fd[1]);
	if (data->cmd)
		execve(data->cmd_path, data->line_splitted, data->envp);
	return (0);
}

int	child_3(t_data *data)
{
	if (data->fd_out)
	{
		dup2(data->fd_out, 1);
		close(data->fd_out);
	}
	dup2(data->fd[0], 0);
	close(data->fd[0]);
	close(data->fd[1]);
	if (data->cmd)
		execve(data->cmd_path, data->line_splitted, data->envp);
	return (0);
}
