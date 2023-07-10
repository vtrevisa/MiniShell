/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_perm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:36:56 by romachad          #+#    #+#             */
/*   Updated: 2023/07/10 10:53:06 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	exec_null(t_pipe *args, t_data *data)
{
	if (args->fpath == NULL)
	{
		if (data->rcode != 127)
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			ft_printf("minishell: %s: command not found\n", \
					data->full_cmd[args->cmd_n][0]);
		}
		close_pipes(args, data);
		return (127);
	}
	if (access(args->fpath, X_OK) != 0)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		ft_printf("minishell: %s: Permission denied\n", args->fpath);
		close_pipes(args, data);
		return (126);
	}
	return (0);
}

int	check_perm_cmd(t_pipe *args, t_data *data)
{
	struct stat	status;
	int			code;

	code = exec_null(args, data);
	if (code != 0)
		return (code);
	if (stat(args->fpath, &status) != 0)
	{
		perror("minishell stat failed");
		return (1);
	}
	if (S_ISDIR(status.st_mode))
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		ft_printf("minishell: %s: Is a directory\n", args->fpath);
		close_pipes(args, data);
		return (126);
	}
	return (0);
}
