/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_input_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:47:49 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/21 13:00:29 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	free_args(t_pipe *args)
{
	free(args->pid);
	free(args->pipes);
}

void	close_pipes(t_pipe *args, t_data *data)
{
	int	i;

	i = -1;
	while (++i < (data->qtd_cmd) * 2)
		close(args->pipes[i]);
}

int	create_pipes(t_pipe *args, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < data->qtd_cmd)
	{
		if (pipe(&args->pipes[j]) == -1)
			return (-1);
		j += 2;
	}
	return (0);
}
