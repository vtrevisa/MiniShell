/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:05:07 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/16 08:09:55 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	if_cmd_redir(t_data *data, t_pipe *args, int *fd)
{
	if (data->cmd_redir[args->cmd_n][0][0] == '0')
		*fd = open(data->cmd_redir[args->cmd_n][0] + 1, \
	O_WRONLY | O_CREAT, 0664);
	else
		*fd = open(data->cmd_redir[args->cmd_n][0] + 1, \
	O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (*fd == -1)
		return (1);
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
	return (0);
}

void	call_exec(t_data *data, t_pipe *args)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(args->fpath, data->full_cmd[args->cmd_n], data->envp);
	free(args->fpath);
}
