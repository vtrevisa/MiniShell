/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:35:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/17 15:25:08 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	child(t_data *data, int fd_in, int fd_out)
{
	execve(data->cmd, data->args1, envp);
	return (0);
}

int	do_cmd(t_data *data)
{
	int	err;
	int pid[]

	err = 0;
	if (pipe(data->fd) == -1)
		return (1);
	
}

void	dealcmd(t_data *data)
{
	data->cmd[0] = data->line_splitted[index];
	if (data->lexed_class[index + 1] == 2)
	{
		data->cmd[1] = data->line_splitted[index + 1];
		data->cmd[2] = "\0";
	}
	else
	{
		data->cmd[1] = "\0";
		data->cmd[2] = "\0";
	}
	do_cmd();
}

int	execute(t_data *data)
{
	int	index;
	int	stdin;
	int	stdout;

	index = 0;
	stdin = 0;
	stdout = 1;
	while(data->line_splitted[index])
	{
		if (data->lexed_class[index] == 1)
			dealcmd(data)
		if (data->lexed_class[index] == 3)
			
		if (data->lexed_class[index] == 4)
		if (data->lexed_class[index] == 5)
		if (data->lexed_class[index] == 6)
		if (data->lexed_class[index] == 7)
		if (data->lexed_class[index] == 8)
		{}
	}
}