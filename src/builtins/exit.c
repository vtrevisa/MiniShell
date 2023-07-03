/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 04:04:24 by romachad          #+#    #+#             */
/*   Updated: 2023/07/03 01:52:01 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	exit_shell(t_data *data)
{
	if (data->linetyped == 1)
	{
		free_full_cmd(data);
		free(data->cmd_redir);
		free(data->full_cmd);
		free(data->line);
	}
	free(data->user);
	free(data->cmd);
	free_char_array(data->envp);
	free_char_array(data->paths);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(0);
}

void	exit_child(t_data *data, int code)
{
	if (data->linetyped == 1)
	{
		free_full_cmd(data);
		free(data->cmd_redir);
		free(data->full_cmd);
		free(data->line);
	}
	free(data->user);
	free(data->cmd);
	free_char_array(data->paths);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(code);
}
